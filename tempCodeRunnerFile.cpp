	BarChart bc(3);
	bc.setFrame("1950");
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	string red("\033[1;36m");
	string blue("\033[1;33m");
	map<string, string> colorMap;
	colorMap["US"] = red;
	colorMap["France"] = blue;
	bc.graph(cout, colorMap, 3);
}