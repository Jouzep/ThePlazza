#include <criterion/criterion.h>
#include "../src/Kitchen.hpp"
#include "../src/Reception.hpp"
#include "../src/Parsing/Parsing.hpp"
#include "../src/Error/Error.hpp"
#include "../src/Encapsulation/IPC.hpp"
#include "../src/Encapsulation/Platform.hpp"
#include "../src/Encapsulation/Process.hpp"

/** PARSING **/

Test(Parsing, parsing_error_args)
{
    const char *av[] = {"./plazza", "ok"};
    int ac = 2;

    cr_assert_throw({
        Parsing pars(ac, av);
    }, Error)
}

Test(Parsing, parsing_correct_args)
{
    const char *av[] = {"./plazza", "2", "2", "1000"};
    int ac = 4;

    cr_assert_no_throw({
        Parsing pars(ac, av);
    }, Error)
}

Test(Parsing, parsing_neg_nbr)
{
    const char *av[] = {"./plazza", "-2", "2", "1000"};
    int ac = 4;

    cr_assert_throw({
        Parsing pars(ac, av);
    }, Error)
}

Test(Parsing, parsing_invalid_conversion)
{
    const char *av[] = {"./plazza", "a", "2", "1000"};
    int ac = 4;

    cr_assert_throw({
        Parsing pars(ac, av);
    }, Error)
}

Test(Parsing, parsing_get_mutiplier)
{
    const char *av[] = {"./plazza", "2", "2", "1000"};
    int ac = 4;

    Parsing pars(ac, av);

    cr_assert_eq(pars.getMultiplier(), 2);
}

Test(Parsing, parsing_get_nbrCooks)
{
    const char *av[] = {"./plazza", "2", "2", "1000"};
    int ac = 4;

    Parsing pars(ac, av);

    cr_assert_eq(pars.getNbCooks(), 2);
}

Test(Parsing, parsing_get_refill_time)
{
    const char *av[] = {"./plazza", "2", "2", "1000"};
    int ac = 4;

    Parsing pars(ac, av);

    cr_assert_eq(pars.getRefillTime(), 1000);
}

/** ENCAPSULATION **/
Test(Encapsulation, encacpsulation_process)
{
    cr_assert_eq(Process::getpid(), getpid());

    pid_t pid = Process::fork();

    cr_assert_neq(pid, -1);
    if (pid == 0) {
        exit(0);
    }
}

Test(Encapsulation, encacpsulation_platform)
{
    pid_t pid = Process::fork();

    cr_assert_neq(pid, -1);
    if (pid == 0) {
        Platform::exit(0);
    }
}

Test(Encapsulation, encacpsulation_message_queue)
{
    cr_expect_neq(IPC::ftok(".", 5), -1);
}

Test(Reception, reception_run)
{
    const char *av[] = {"./plazza", "2", "2", "1000"};
    int ac = 4;

    Parsing pars(ac, av);

    // Plazza::Reception reception(pars, false);
}

Test(Kitchen, kitchen_run)
{
    std::vector<std::string> ingredients = {};
    // Plazza::Kitchen kitchen(2, 2, 2000, 5000, ingredients);
    // std::array<int, 2> fd = {1, 1};
    // Plazza::Kitchen kitchen(2, 2, 1000, fd);

    // kitchen.run();
    // cr_assert_eq(kitchen.isStaturated(), false);
}

Test(Kitchen, kitchen_saturated)
{
    // std::array<int, 2> fd = {1, 1};
    // Plazza::Kitchen kitchen(2, 2, 1000, fd);

    // cr_assert_eq(kitchen.isStaturated(), false);
}

Test(Kitchen, kitchen_receive_order)
{
    // std::array<int, 2> fd = {1, 1};
    // Plazza::Kitchen kitchen(2, 2, 1000, fd);

    // std::vector<Plazza::Order> orderList = {
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M),
    //     Plazza::Order(Plazza::PizzaType::Regina, Plazza::PizzaSize::M)
    // };

    // kitchen.receiveOrder(orderList);
    // cr_assert_eq(orderList.size(), 1);
}