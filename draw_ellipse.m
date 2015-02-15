function draw_ellipse(x, y, a, b, angle)

steps = 64;
points = []; 
beta = angle;
sinbeta = sin(beta);
cosbeta = cos(beta);
 
for i = 0:360/steps:360 
  
    alpha = i * (pi / 180) ;
    sinalpha = sin(alpha);
    cosalpha = cos(alpha);
 
    X = x + (a * cosalpha * cosbeta - b * sinalpha * sinbeta);
    Y = y + (a * cosalpha * sinbeta + b * sinalpha * cosbeta);
    points = [points; X Y];
end
hold on
plot(points(:,1), points(:,2),'k','LineWidth',1.3);
end
