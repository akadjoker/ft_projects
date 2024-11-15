#include "ft_nm.h"

static int buffer_nm(const Elf64_Ehdr *Ehdr, const Elf64_Shdr *Shdrt,
                     const char *shstrtab, const Elf64_Sym *Ssymtab,
                     const char *Sstrtab, int symb_nb,
                     const unsigned int *smax)
{
  unsigned int j = 0, ret, shstrtabndx;
  size_t bufsize = symb_nb * SYMBUFSIZE * sizeof(char);
  char *output_buf = (char *)malloc(bufsize);
  t_rbt *root = NULL;

  if (!output_buf)
    return EXIT_FAILURE;
  ft_bzero(output_buf, symb_nb * SYMBUFSIZE);

  for (int i = 1; i < symb_nb; i++)
  {
    if (Ssymtab[i].st_shndx > Ehdr->e_shnum &&
        !is_special_section_indice(Ssymtab[i].st_shndx))
      return error_wrap(OOPS_BAD_SYMTAB, root, output_buf);
    if (is_special_section_indice(Ssymtab[i].st_shndx) ||
        ELF64_ST_TYPE(Ssymtab[i].st_info) == STT_SECTION)
      continue;
    shstrtabndx = Shdrt[Ssymtab[i].st_shndx].sh_name;
    if (shstrtabndx > smax[SHSTRTAB] || Ssymtab[i].st_name > smax[STRTAB])
      return error_wrap(OOPS_BAD_STRTAB, root, output_buf);
    format_output(&root, Ssymtab[i].st_value, &Sstrtab[Ssymtab[i].st_name],
                  Ssymtab[i].st_info, Ssymtab[i].st_shndx,
                  &shstrtab[shstrtabndx], 64);
    j++;
  }

  if (!getargs(ARG_P))
  {
    ret = rbt_to_buf(root, output_buf, 0);
    write(STDOUT_FILENO, output_buf, ret);
  }

  destroy_rbt(root);
  free(output_buf);
  return EXIT_SUCCESS;
}

static int handle_symtab(const void *file, const Elf64_Ehdr *Ehdr,
                         const Elf64_Shdr *Shdrt, int symtab, size_t filesize)
{
  unsigned int symb_nb = 0, strtab = Shdrt[symtab].sh_link, smax[2];
  char *Sstrtab, *Sshstrtab;
  Elf64_Sym *Ssymtab;

  if (sizeof(*Ssymtab) != Shdrt[symtab].sh_entsize ||
      Shdrt[symtab].sh_link >= Ehdr->e_shnum ||
      Ehdr->e_shstrndx >= Ehdr->e_shnum ||
      filesize < Shdrt[strtab].sh_offset + Shdrt[strtab].sh_size ||
      filesize < Shdrt[symtab].sh_offset + Shdrt[symtab].sh_size ||
      filesize <
          Shdrt[Ehdr->e_shstrndx].sh_offset + Shdrt[Ehdr->e_shstrndx].sh_size)
    return oops_error(OOPS_BAD_SYMTAB);

  Sstrtab = (char *)(file + Shdrt[strtab].sh_offset);
  Sshstrtab = (char *)(file + Shdrt[Ehdr->e_shstrndx].sh_offset);
  Ssymtab = (Elf64_Sym *)(file + Shdrt[symtab].sh_offset);
  smax[STRTAB] = Shdrt[strtab].sh_size;
  smax[SHSTRTAB] = Shdrt[Ehdr->e_shstrndx].sh_size;

  for (unsigned long i = 0; i < Shdrt[symtab].sh_size; i += sizeof(*Ssymtab))
  {
    symb_nb++;
  }

  return buffer_nm(Ehdr, Shdrt, Sshstrtab, Ssymtab, Sstrtab, symb_nb, smax);
  return EXIT_SUCCESS;
}

int ft_nm_x64(const void *file, size_t filesize)
{
  Elf64_Ehdr Ehdr;
  Elf64_Shdr *Shdrt;
  int symtab = -1, ret;

  if (filesize < sizeof(Ehdr))
    return oops_error(OOPS_NOTELF);
  ft_memcpy(&Ehdr, file, sizeof(Ehdr));
  if (!Ehdr.e_shnum || !Ehdr.e_shoff || Ehdr.e_version == EV_NONE ||
      filesize < Ehdr.e_shoff + (sizeof(*Shdrt) * Ehdr.e_shnum) ||
      Ehdr.e_shentsize != sizeof(*Shdrt))
    return oops_error(OOPS_BAD_ELF);

  /* print_Ehdr(&Ehdr); */
  Shdrt = (Elf64_Shdr *)(file + Ehdr.e_shoff);

  if (Shdrt[0].sh_size != 0 && Shdrt[0].sh_offset != 0)
    return oops_error(OOPS_BAD_SHDR);
  if (Ehdr.e_shstrndx >= Ehdr.e_shnum ||
      Shdrt[Ehdr.e_shstrndx].sh_type != SHT_STRTAB)
  {
    oops_error(OOPS_BAD_SYMTAB);
    return EXIT_SUCCESS;
  }
  for (int i = 0; i < Ehdr.e_shnum; i++)
  {
    if (Shdrt[i].sh_name > Shdrt[Ehdr.e_shstrndx].sh_size)
      return oops_error(OOPS_BAD_SHDR);
    if (Shdrt[i].sh_type == SHT_SYMTAB)
      symtab = i;
    /* print_Shdr(&(Shdrt[i]), i); */
  }
  if (symtab > -1)
    ret = handle_symtab(file, &Ehdr, Shdrt, symtab, filesize);
  else
    return oops_error(OOPS_BAD_SYMTAB);
  return ret;
}
