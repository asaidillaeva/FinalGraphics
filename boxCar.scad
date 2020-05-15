

difference(){
    color("white", 100)
    cube(170,170);
    translate([5, 5, 5, ])
    cube([160, 160, 165]);
    
    translate([20, 2, 135])
     sphere(d = 10);
    
    translate([20, 168, 135])
    sphere(d = 10);
    
}



difference(){
    color("white", 100)
    translate([200, 0, 0])
    cube([180, 180, 20]);
    
    translate([205, 5, 5])
    cube([170, 171, 25]);
    
    translate([230, 30, 0])
    cube([40, 120, 120]);
    }
