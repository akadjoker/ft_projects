#include <iostream>
#include <chrono>
#include "state_machine.hpp"


enum class State
{
    Idle,
    Running,
    Paused,
    Stopped
};

void teste_42()
{

    StateMachine<State> sm;

    sm.addState(State::Idle);
    sm.addState(State::Running);
    sm.addState(State::Paused);
    sm.addState(State::Stopped);

    sm.addAction(State::Idle, []
                 { std::cout << "System is idle." << std::endl; });
    sm.addAction(State::Running, []
                 { std::cout << "System is running." << std::endl; });
    sm.addAction(State::Paused, []
                 { std::cout << "System is paused." << std::endl; });
    // No addAction for State::Stopped, it will use the default empty lambda

    sm.addTransition(State::Idle, State::Running, []
                     { std::cout << "Transitioning from Idle to Running." << std::endl; });
    sm.addTransition(State::Running, State::Paused, []
                     { std::cout << "Transitioning from Running to Paused." << std::endl; });
    sm.addTransition(State::Paused, State::Running, []
                     { std::cout << "Transitioning from Paused to Running." << std::endl; });
    // No addTransition for State::Stopped

    sm.update();                     // Should print: "System is idle."
    sm.transitionTo(State::Running); // Should print: "Transitioning from Idle to Running."
    sm.update();                     // Should print: "System is running."
    sm.transitionTo(State::Paused);  // Should print: "Transitioning from Running to Paused."
    sm.update();                     // Should print: "System is paused."

    // Transitioning to and from the new State::Stopped
    try
    {
        sm.transitionTo(State::Stopped); // Should not print any transition message, and throw an exception
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl; // Handle state not found
    }

    try
    {
        sm.transitionTo(State::Stopped); // Should not print anything, default empty lambda is executed
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl; // Handle state not found
    }

    try
    {
        sm.transitionTo(State::Running); //??? Should not print any transition message, and throw an exception ??? 
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl; // Handle state not found
    }
}

void test_stateAction()
{
    try
    {
        StateMachine<std::string> machine;
        machine.addState("StateA");
        machine.addState("StateB");

        bool actionExecuted = false;

        machine.addAction("StateA", [&]()
                          { actionExecuted = true; });

        machine.update();
        if (actionExecuted)
        {
            std::cout << "Test Passed: State action executed." << std::endl;
        }
        else
        {
            std::cout << "Test Failed: State action not executed." << std::endl;
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Test Failed: " << e.what() << std::endl;
    }
}
void test_fullStateCycle()
{
    StateMachine<std::string> machine;
    machine.addState("StateA");
    machine.addState("StateB");
    machine.addState("StateC");

    machine.addTransition("StateA", "StateB", []()
                          { std::cout << "Transitioned from StateA to StateB" << std::endl; });

    machine.addTransition("StateB", "StateC", []()
                          { std::cout << "Transitioned from StateB to StateC" << std::endl; });

    machine.addTransition("StateC", "StateA", []()
                          { std::cout << "Transitioned from StateC to StateA" << std::endl; });

    try
    {
        machine.transitionTo("StateB");
        machine.transitionTo("StateC");
        machine.transitionTo("StateA"); // Completa o ciclo

        std::cout << "Test Passed: Completed state cycle." << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Test Failed: " << e.what() << std::endl;
    }
}

void test_circularTransition()
{
    StateMachine<std::string> machine;
    try
    {

        machine.addState("State1");
        machine.addState("State2");

        machine.addTransition("State1", "State2", []()
                              { std::cout << "Transitioning to State2" << std::endl; });

        machine.addTransition("State2", "State1", []()
                              { std::cout << "Returning to State1" << std::endl; });

        machine.transitionTo("State2");
        machine.transitionTo("State1"); // Testa a transição circular

        std::cout << "Test Passed: Circular transition successful." << std::endl;
    }

    catch (const std::exception &e)
    {
        std::cout << "Test Failed: " << e.what() << std::endl;
    }
}

void test_performance()
{
    try
    {

        StateMachine<std::string> machine;

        for (int i = 0; i < 1000; ++i)
        {
            machine.addState("State" + std::to_string(i));
        }

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 999; ++i)
        {
            machine.addTransition("State" + std::to_string(i), "State" + std::to_string(i + 1), []() {});
        }

        for (int i = 0; i < 999; ++i)
        {
            machine.transitionTo("State" + std::to_string(i + 1));
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Performance test completed in " << elapsed.count() << " seconds." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Test Failed: " << e.what() << std::endl;
    }
}
void test_transitionToInvalidState()
{
    StateMachine<std::string> machine;
    machine.addState("StateA");

    try
    {
        machine.transitionTo("StateB"); // Estado "StateB" não existe
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Test Passed: Caught exception: " << e.what() << std::endl;
    }
}

void test_transitionWithoutAction()
{
    StateMachine<std::string> machine;
    machine.addState("StateA");
    machine.addState("StateB");

    // Define uma transição sem lambda
    machine.addTransition("StateA", "StateB", nullptr);

    try
    {
        machine.transitionTo("StateB"); // Testar transição sem lambda
    }
    catch (const std::bad_function_call &e)
    {
        std::cout << "Test Passed: Caught bad_function_call: " << e.what() << std::endl;
    }
}

void test_stateWithoutAction()
{
    StateMachine<std::string> machine;
    machine.addState("StateA");

    try
    {
        machine.update(); // Nenhuma ação associada ao estado "StateA"
        std::cout << "Test Passed: Default state action executed."  << std::endl;

    }
    catch (const std::exception &e)
    {
        std::cout << "Test Failed: Caught : " << e.what() << std::endl;
    }
}

int main()
{

    teste_42();
    test_stateAction();
    test_fullStateCycle();
    test_circularTransition();
    test_performance();

    test_transitionToInvalidState();

    test_transitionWithoutAction();
    test_stateWithoutAction();

    return 0;
}