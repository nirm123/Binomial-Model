import math
from scipy.stats import norm

# Problem 1
S = 100
K = 100

r = 0.05
q = 0.04
T = 1
o = 0.2

d1 = (math.log(S/K) + (r - q + (0.5 * o**2)) * T) / (o * math.sqrt(T))
d2 = d1 - (o * math.sqrt(T))

npd1 = norm.cdf(d1)
npd2 = norm.cdf(d2)
nnd1 = norm.cdf(-d1)
nnd2 = norm.cdf(-d2)

c = S * math.exp(-q * T) * npd1 - K * math.exp(-r * T) * npd2
p = -S * math.exp(-q * T) * nnd1 + K * math.exp(-r * T) * nnd2

#print("d1: " + str(d1))
#print("d2: " + str(d2))
#print("N(d1): " + str(npd1))
#print("N(d2): " + str(npd2))
#print("N(-d1): " + str(nnd1))
#print("N(-d2): " + str(nnd2))
print("Call Price: " + str(c))
#print("Put Price: " + str(p))

# Problem 2
S = 0.75

r = 0.027
q = 0.014
o = 0.15
T = 0.5
N = 2
s = T/N
t = 1/6

K = S * math.exp((r - q) * t)
u = math.exp(o * math.sqrt(s))
d = math.exp(-o * math.sqrt(s))
p = (math.exp((r - q) * s) - d)/(u-d)

S22 = u**2 * S
S21 = u * d * S
S20 = d**2 * S

fuu = max(K - S22, 0)
fud = max(K - S21, 0)
fdd = max(K - S20, 0)

S11 = u * S
S10 = d * S

fu = math.exp(-r*s)*(p*fuu+(1-p)*fud)
fd = max(K-S10, 0)

#print("u: " + str(u))
#print("d: " + str(d))
#print("K: " + str(K))
#print("p: " + str(p))
#print("S22: " + str(S22))
#print("S21: " + str(S21))
#print("S20: " + str(S20))
#print("fuu: " + str(fuu))
#print("fud: " + str(fud))
#print("fdd: " + str(fdd))
#print("S11: " + str(S11))
#print("S10: " + str(S10))
#print("fu: " + str(max(K-S11, 0)) + " " + str(math.exp(-r*s)*(p*fuu+(1-p)*fud)))
#print("fd: " + str(max(K-S10, 0)) + " " + str(math.exp(-r*s)*(p*fud+(1-p)*fdd)))
#print("f0 " + str(max(K-S, 0)) + " " + str(math.exp(-r*s)*(p*fu+(1-p)*fd)))

# Problem 3
o = 0.2
s = 0.25
S = 100
r = 0.027

u = math.exp(o * math.sqrt(s))
d = math.exp(-o * math.sqrt(s))

S22 = u**2*S
S21 = u*d*S
S20 = d**2*S
S11 = u*S
S10 = d*S
p = (math.exp(r*s) - d)/(u-d)

fuu = max((S22 - (S+S11+S22)/3), 0)
fud = max((S21 - (S+S11+S21)/3), 0)
fdu = max((S21 - (S+S10+S21)/3), 0)
fdd = max((S20 - (S+S10+S20)/3), 0)
fu = math.exp(-r*s)*(p*fuu+(1-p)*fud)
fd = math.exp(-r*s)*(p*fdu+(1-p)*fdd)
f = math.exp(-r*s)*(p*fu+(1-p)*fd)
#print(f)
delta = (fuu - fud)/(u*S*(u-d))
#print(1000000*delta)
