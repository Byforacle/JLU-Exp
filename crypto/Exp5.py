from c1 import encrypt as encrypt_fesital
from c2 import *
import tqdm
import secrets

BLOCK_SIZE = 16

def OFB_encrypt_or_decrypt(key: bytes, msg: bytes):
    TAP = [1, 2, 4]
    iv = key
    return b''.join([bytes([a ^ b for a, b in zip(msg[ind : ind + BLOCK_SIZE], encrypt_fesital(iv, key, TAP)[0])]) for ind in tqdm.tqdm(range(0, len(msg), BLOCK_SIZE))])

def get_session_key():
    return secrets.token_bytes(BLOCK_SIZE)
