 function [P] = draw_line(V, O, C, L)
 
 if nargin == 3
     L = '-';
 
 elseif nargin == 2
    C = 0;
    L = '-';
 
 elseif nargin == 1
    O = [0 0];
    C = 0;
    L = '-';
 end
 
     lineX = [O(1) V(1)];
     lineY = [O(2) V(2)];
     P = line(lineX, lineY);
     if C
          P.Color = C;  
     end

     P.LineStyle = L;
 end