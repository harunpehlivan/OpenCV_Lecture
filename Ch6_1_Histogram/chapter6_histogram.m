

o = [60, 61, 62, 63, 64, 65];
t = [0, 255];
oMin = min(o);
oMax = max(o);
tMin = min(t);
tMax = max(t);
ratio = (tMax-tMin)/(oMax-oMin);
stretch=(o-oMin)*ratio

