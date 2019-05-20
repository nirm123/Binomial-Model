import math
from scipy.stats import norm

# Problem 2
K = 100
S = 100
r = 0.05
q = 0.04
sig = 0.2
T = 1

d1 = ((math.log(S / K) + (r - q + 0.5 * (sig ** 2)) * T) / (sig * math.sqrt(T)))
d2 = d1 - (sig * math.sqrt(T))
call_price = (S * math.exp(-q * T) * norm.cdf(d1) - K * math.exp(-r * T) * norm.cdf(d2))

print("d1 = " + str(d1))
print("d2 = " + str(d2))
print("Call Price = $" + str(call_price))
