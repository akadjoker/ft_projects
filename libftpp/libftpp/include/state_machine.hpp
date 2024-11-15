
#pragma once


#include <unordered_map>
#include <vector>
#include <functional>
#include <stdexcept>

template <typename TState>
class StateMachine
{
public:
    StateMachine() {}

    void addState(const TState &state)
    {
        if (m_ids.find(state) != m_ids.end())
        {
            throw std::invalid_argument("State already exists");
        }

        size_t stateId = m_states.size();
        m_states.push_back(state);
        m_ids[state] = stateId;
        m_callbacks[state] = empty;
        if (m_states.size() == 1) // definir o primeiro estado como o inicial
        {
            m_currentState = m_states[0];
        }
    }

    void addTransition(const TState &startState, const TState &finalState, const std::function<void()> &lambda)
    {
        if (m_ids.find(startState) == m_ids.end() || m_ids.find(finalState) == m_ids.end())
        {
            throw std::invalid_argument("State not found");
        }

        size_t startStateId = m_ids[startState];
        size_t finalStateId = m_ids[finalState];

        if (startStateId == finalStateId)
        {
            throw std::invalid_argument("Start and final state cannot be the same");
        }

        Transition transition = Transition(startStateId, finalStateId, lambda);
        m_transitions.push_back(std::move(transition));

        m_transitionMap[startState].push_back(m_transitions.size() - 1); // Adicionar a transição ao estado inicial
    }

    void addAction(const TState &state, const std::function<void()> &lambda)
    {
        if (m_ids.find(state) == m_ids.end())
        {
            throw std::invalid_argument("State not found");
        }
        m_callbacks[state] = lambda;
    }

    void transitionTo(const TState &state)
    {
        if (m_ids.find(state) == m_ids.end())
        {
            throw std::invalid_argument("State not found");
        }

        size_t newStateId = m_ids[state];

        // Procurar uma transição válida
        auto &transitions = m_transitionMap[m_currentState];
        bool found = false;

        for (size_t transitionId : transitions)
        {
            Transition &transition = m_transitions[transitionId];
            if (transition.finalState == newStateId)
            {
                transition.lambda(); // Executa a ação de transição
                m_currentState = state; // Atualiza o estado atual
                found = true;
                break;
            }
        }

        if (!found)
        {
            throw std::invalid_argument("No valid transition found from current state");
        }
    }

    void update()
    {
        m_callbacks[m_currentState](); // Executa a ação associada ao estado atual
    }

private:
    static void empty() {};

    struct Transition
    {
        size_t startState;
        size_t finalState;
        std::function<void()> lambda;

        Transition(size_t startState, size_t finalState, const std::function<void()> &lambda)
            : startState(startState), finalState(finalState), lambda(lambda) {}
    };

    std::vector<TState> m_states;  // Armazenar todos os estados
    std::vector<Transition> m_transitions;  // Armazenar todas as transições

    std::unordered_map<TState, std::function<void()>> m_callbacks; // Ações associadas aos estados
    std::unordered_map<TState, size_t> m_ids; // IDs dos estados, is sao os indices da lista de estados "vector" para noa estar usar copy constructors & move constructors e hash maps
    std::unordered_map<TState, std::vector<size_t>> m_transitionMap; // Transições por estado, cada estado pode ter mais que uma transição

    TState m_currentState; // Estado atual
};