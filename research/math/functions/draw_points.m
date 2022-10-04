% Plots the number of targets as green stares.
function [P] = draw_points(points, style)
    
    if nargin == 1 
        s = 'g*';
    
    elseif nargin == 2
        s = style;    
    end 
    
    P = plot(points(:,1),points(:,2),s);
end