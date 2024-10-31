import dns.resolver
import dns.update
import dns.query
import dns.tsigkeyring

# Ganti dengan informasi yang sesuai
DOMAIN = 'example.com'  # Ganti dengan domain yang diinginkan
DNS_SERVER = 'ns1.example.com'  # Ganti dengan server DNS yang ingin digunakan
TSIG_KEY_NAME = 'your-key-name'  # Ganti dengan nama key TSIG
TSIG_KEY_SECRET = 'your-key-secret'  # Ganti dengan secret key untuk TSIG

# Mengambil catatan A dari domain
def query_dns(domain):
    try:
        result = dns.resolver.resolve(domain, 'A')
        for ipval in result:
            print(f'IP Address: {ipval.to_text()}')
    except Exception as e:
        print(f'Error: {e}')

# Menambahkan catatan A ke domain
def add_dns_record(subdomain, ip_address):
    keyring = dns.tsigkeyring.from_text({
        TSIG_KEY_NAME: TSIG_KEY_SECRET
    })
    
    update = dns.update.Update(DOMAIN, keyring=keyring)
    update.add(subdomain, 300, 'A', ip_address)  # Menambahkan catatan A
    response = dns.query.tcp(update, DNS_SERVER)

    print(f'Update response: {response}')

# Contoh penggunaan
if __name__ == '__main__':
    query_dns(DOMAIN)
    add_dns_record('sub.example.com', '114.79.5.250')  # Ganti dengan subdomain yang diinginkan