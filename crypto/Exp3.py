from Crypto.Util.number import *
import math
import random


def get_key_pair(bits):
    p = getPrime(bits)
    q = getPrime(bits)
    n = p * q
    phi = (p - 1) * (q - 1)
    e = random.randrange(1, phi)
    gcd = math.gcd(e, phi)
    while gcd != 1:
        e = random.randrange(1, phi)
        gcd = math.gcd(e, phi)
    d = inverse(e, phi)
    return (e, n), (d, n)


def encrypt(plain_text, public_key):
    e, n = public_key
    cipher_text_long = pow(bytes_to_long(plain_text), e, n)
    return long_to_bytes(cipher_text_long)


def decrypt(cipher_text_bytes, private_key):
    d, n = private_key
    cipher_text_long = bytes_to_long(cipher_text_bytes)
    decrypted_bytes = long_to_bytes(pow(cipher_text_long, d, n))
    return decrypted_bytes

# Generate Key Pairs
public_key_pair, private_key_pair = get_key_pair(256)

message = "happy crypto".encode()
encrypted_message = encrypt(message, public_key_pair)
print("Encrypted:", encrypted_message)

decrypted_message = decrypt(encrypted_message, private_key_pair)
print("Decrypted:", decrypted_message.decode())

server_name = "CaryLap"

public_key_file = "\n".join([
  "-----BEGIN OPENSSH PUBLIC KEY-----",
  f"e:{public_key_pair[0]}",
  f"n:{public_key_pair[1]}",
  f"{server_name=}",
  "-----END OPENSSH PRIVATE KEY-----"])

private_key_file = "\n".join([
  "-----BEGIN OPENSSH PRIVATE KEY-----",
  f"d:{public_key_pair[0]}",
  f"n:{public_key_pair[1]}",
  f"{server_name=}",
  "-----END OPENSSH PRIVATE KEY-----"])
print(f"{public_key_file}")
print()
print(f"{private_key_file}")
