BLOCK_SIZE = 128 // 8
LOOP = 1

sbox = [3, 14, 1, 10, 4, 9, 5, 6, 8, 11, 15, 2, 13, 12, 0, 7]
sbox_rev = [14, 2, 11, 0, 4, 6, 7, 15, 8, 5, 3, 9, 13, 12, 1, 10]


def F_function(input_bytes: bytes, key: bytes) -> bytes:
    out = []
    for i in range(len(input_bytes)):
        # print(hex(input_bytes[i]))
        # replaced = sbox[input_bytes[i]>>4]+sbox[input_bytes[i]&0xf]
        # replaced = input_bytes[i]
        # print(hex(input_bytes[i]),hex(replaced))
        replaced = sbox[input_bytes[i] >> 4]
        out.append(replaced ^ key[i % len(key)])
        replaced = sbox[input_bytes[i] & 0xF]
        out.append(replaced ^ key[i % len(key)])
    # print(out)
    # print(bytes(out).hex())
    return bytes(out)


DDT = [[0 for _ in range(16)] for _ in range(16)]
for c in range(16):
    for d in range(16):
        DDT[c ^ d][sbox[c] ^ sbox[d]] += 1

msg_origin = b"\x00\x00\x01\x10"
msg_origin_xor = bytes([b ^ 4 for b in msg_origin])
key = b"\x12"
tap_position = [1, 3, 4, 9]
enc, fill = encrypt(msg_origin, key, tap_position)
enc1, fill1 = encrypt(msg_origin_xor, key, tap_position)
# msg = decrypt(enc,key,tap_position, fill)
print(f"{msg_origin = }")
print(f"{msg_origin_xor = }")
print(f"{enc.hex() = }")
print(f"{enc1.hex() = }")
for i, v in enumerate(enc):
    # print(hex(enc[i]))
    print((enc[i] >> 4) ^ (enc1[i] >> 4))
    print((enc[i] & 0xF) ^ (enc1[i] & 0xF))
    if i // 2 > len(enc) - fill:
        Break

chardat0 = [0] * 16
chardatmax = 0


def gen_char_data(indiff, outdiff):
    print(f"Generating possible intermediate values based on differential({indiff} --> {outdiff}):")

    global chardatmax
    chardatmax = 0
    for f in range(16):
        my_comp = f ^ indiff

        if sbox[f] ^ sbox[my_comp] == outdiff:
            print(f"  Possibles:   {f} ^ {indiff} = {my_comp} --> {sbox[f]} + {sbox[my_comp]}")
            chardat0[chardatmax] = f
            chardatmax += 1


gen_char_data(6, 6)
