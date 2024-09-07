import random
import math
from Crypto.Util import *
from Crypto.Util.number import *
from Crypto.PublicKey import RSA

# 生成RSA密钥对
def generate_key_pair():
    p = getPrime(128)
    q = getPrime(128)
    n = p * q
    phi_n = (p - 1) * (q - 1)
    e = 65537  # 选择公开指数e
    gcd = math.gcd(e, phi_n)
    while gcd != 1:
        e = random.randrange(1, phi_n)
        gcd = math.gcd(e, phi_n)
    d = inverse(e, phi_n)  # 计算私钥d
    public_key = RSA.construct((n, e))
    private_key = RSA.construct((n, e, d))
    return public_key, private_key

# 盲化消息
def blind_message(message, public_key):
    n = public_key.n
    while True:
        r = random.randrange(1, n)
        gcd = math.gcd(r, n)
        if gcd == 1: break
    blind_factor = pow(r, public_key.e, n)
    blinded_message = (message * blind_factor) % n
    return blinded_message, r

# 盲签名
def blind_sign(blinded_message, private_key):
    return pow(blinded_message, private_key.d, private_key.n)

# 解盲化签名
def unblind_signature(blinded_signature, blind_factor, public_key):
    n = public_key.n
    return (blinded_signature * inverse(blind_factor, n)) % n
# 示例
message = 12345
# 生成密钥对
public_key, private_key = generate_key_pair()
# 盲化消息
blinded_message, r = blind_message(message, public_key)
# 盲签名
blinded_signature = blind_sign(blinded_message, private_key)
# 解盲化签名
signature = unblind_signature(blinded_signature, r, public_key)

print("原始消息:", message)
print("盲化后的消息:", blinded_message)
print("盲签名后的消息:", blinded_signature)
print("解盲化签名后的消息:", signature)

assert pow(message, private_key.d, public_key.n) == signature
