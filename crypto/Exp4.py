import random
import gmpy2
from Crypto.Util.number import getPrime, isPrime, sieve_base as primes

def myPrime(bits):
    while True:
        n = 2
        while n.bit_length() < bits:
            n *= random.choice(primes)
        if isPrime(n + 1):
            return n + 1

p = myPrime(300)
q = getPrime(300)
N = p * q
print(N)
a = 2
n = 2
while True:
    a = pow(a, n, N)
    res = gmpy2.gcd(a - 1, N)
    if res != 1 and res != N:
        q = N // res
        print(f"{n = }")
        print(f"p = {res}")
        print(f"{q = }")
        break
    n += 1
# 成功分解大整数N
import gmpy2

# 两个很近的素数
p = getPrime(1024)
q = gmpy2.next_prime(p)
n = p * q
print(f"{p=}")
print(f"{q=}")
print(f"{n=}")

# 开根号
temp = gmpy2.iroot(n, 2)[0]
p1 = gmpy2.next_prime(temp)
q1 = n // p1
print(f"{q==p1}\t{q==q1}")
print(f"{p==p1}\t{p==q1}")
