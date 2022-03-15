import Module_C;
import <iostream>;


int main()
{
    std::cout << "============== Task 6 ================\n";

    Player P1(NS::x1, NS::y1, NS::s1);
    Player P2(NS::x2, NS::y2, NS::s2);
    Player P3(NS::x3, NS::y3, NS::s3);
    Player P4(NS::x4, NS::y4, NS::s4);
    Player P5(NS::x5, NS::y5, NS::s5);

    P1.print_player();
    P2.print_player();
    P3.print_player();
    P4.print_player();
    P5.print_player();

    std::cout << "============== Task 10 ================\n";

    change_int();
    change_double();
    change_string(); 

    Player P6(NS::x1, NS::y1, NS::s1);
    Player P7(NS::x2, NS::y2, NS::s2);
    Player P8(NS::x3, NS::y3, NS::s3);
    Player P9(NS::x4, NS::y4, NS::s4);
    Player P10(NS::x5, NS::y5, NS::s5);

    std::cout << "Players after change: \n";
    P6.print_player();
    P7.print_player();
    P8.print_player();
    P9.print_player();
    P10.print_player();

    std::cout << std::endl;

    std::cout << "============== Task 10 ================\n";

    std::cout <<"Variable in Module_A Before change: " << test_int << std::endl;
    access_test();
    std::cout << "Variable in Module_A After change: " << test_int << std::endl;
    std::cout << std::endl;

    access_test1();
}