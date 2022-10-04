function [originUnit, relativeUnit, P ] = drawBoat(boat)
    % constants
    radian = 0.01745329;
    
    boatDir = boat(3)*radian;
    originUnit = [1*cos(boatDir) 1*sin(boatDir)];
    relativeUnit = boat(1:1:2)+originUnit;
    P = plot(boat(1),boat(2), 'bo');
    hold on
    drawVector(originUnit,boat(1,1:2));
    

end