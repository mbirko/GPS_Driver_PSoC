% combines drawBoat, DrawTargets in one call. 
% calculates the vector drawn from the boat to the first entry in targets
function [V_boat_to_target] = draw_boat_n_target(boat, targets)
    drawBoat(boat);
    drawTargets(targets);
    V_boat_to_target = targets(1,:)-boat(1,(1:2));
    drawVector(V_boat_to_target, boat(1,(1:2)), 'r','.');
end