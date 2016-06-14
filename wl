pov{
        pos(0,7,23)
        dir(0,0,0)
}

spot{
        color(256,256,256)
        pos(0,10,2)
        int(90);
}

spot{
	color(256,256,256)
        pos(0,5,10)
        int(90);
}

spot{
        color(256,256,256)
        pos(10,0,0)
        int(100);
}

spot{
        color(256,256,256)
        pos(6,14,2)
        int(90);
}

cylinder{
	rot(90,0,0)
	neg(1)
	pos(0,0,2)
	size(300)
}

cylinder{
        rot(0,0,0)
        neg(1)
        pos(0,0,2)
        size(300)
}

sphere{
	neg(0)
	pos(0,0,2)
	size(900)
	color(256,256,256)
}

plane{
	rot(0,1,0)
	pos(0,-1,0);
}

plane{
	color(256,0,0)
        rot(0,1,0)
        pos(0,30,0);
}
