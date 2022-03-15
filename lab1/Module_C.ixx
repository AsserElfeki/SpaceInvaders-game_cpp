export import Module_B;
export module Module_C;

export void change_int()
{
	NS::x1 *= 2;
	NS::x2 *= 2;
	NS::x3 *= 2;
	NS::x4 *= 2;
	NS::x5 *= 2;
}

export void change_double() {
	NS::y1 += 2.5;
	NS::y2 = 89.3;
	NS::y3 = 8.3;
	NS::y4 = 9.1;
	NS::y5 = 4.7;
}

export void change_string() {
	NS::s1 = "Elfeki";
	NS::s2 = "Didyk";
	NS::s3 = "Bobchuk";
	NS::s4 = "Smaluch";
	NS::s5 = "Albali";
}

export void access_test() {
	test_int += 1;
}

export void access_test1() {
	Player test_player( 00.01 , 00.02 , "test player");
	std::cout << "Hurraaaay, you figured it out\n";
	test_player.print_player();
}

