# 概要
h2loadを使うとHTTP/2ベンチマークを測定することができる。

# 詳細

### HTTP/2サーバのベンチマークを測定する
次の例は8080で可動しているHTTP/2サーバに対して同時並列数10で、合計10000リクエストを送出するベンチマークです。
```
$ h2load -c 10 -n 10000 https://127.0.0.1:8080
starting benchmark...
spawning thread #0: 10 total client(s). 10000 total requests
TLS Protocol: TLSv1.2
Cipher: ECDHE-RSA-AES256-GCM-SHA384
Server Temp Key: ECDH P-256 256 bits
Application protocol: h2
progress: 10% done
progress: 20% done
progress: 30% done
progress: 40% done
progress: 50% done
progress: 60% done
progress: 70% done
progress: 80% done
progress: 90% done
progress: 100% done

finished in 2.65s, 3771.19 req/s, 645.05KB/s
requests: 10000 total, 10000 started, 10000 done, 0 succeeded, 10000 failed, 0 errored, 0 timeout
status codes: 0 2xx, 0 3xx, 10000 4xx, 0 5xx
traffic: 1.67MB (1751520) total, 98.91KB (101280) headers (space savings 91.83%), 1.40MB (1470000) data
                     min         max         mean         sd        +/- sd
time for request:      144us    104.30ms      2.49ms      4.01ms    92.92%
time for connect:    89.51ms     95.26ms     91.30ms      2.15ms    80.00%
time to 1st byte:    94.39ms     97.07ms     95.24ms       985us    80.00%
req/s           :     377.32      389.89      384.03        4.62    60.00%
```

### プロトコルを指定する

pオプションの後に「http/1.1」や「h2c」を指定することができます。
```
$ h2load -p http/1.1 -c 10 -n 10000 https://127.0.0.1:8080
starting benchmark...
spawning thread #0: 10 total client(s). 10000 total requests
TLS Protocol: TLSv1.2
Cipher: ECDHE-RSA-AES256-GCM-SHA384
Server Temp Key: ECDH P-256 256 bits
Application protocol: h2
progress: 10% done
progress: 20% done
progress: 30% done
progress: 40% done
progress: 50% done
progress: 60% done
progress: 70% done
progress: 80% done
progress: 90% done
progress: 100% done

finished in 3.12s, 3204.85 req/s, 548.18KB/s
requests: 10000 total, 10000 started, 10000 done, 0 succeeded, 10000 failed, 0 errored, 0 timeout
status codes: 0 2xx, 0 3xx, 10000 4xx, 0 5xx
traffic: 1.67MB (1751520) total, 98.91KB (101280) headers (space savings 91.83%), 1.40MB (1470000) data
                     min         max         mean         sd        +/- sd
time for request:      145us     94.16ms      2.95ms      4.99ms    91.85%
time for connect:   101.64ms    110.46ms    104.80ms      2.96ms    70.00%
time to 1st byte:   109.09ms    112.93ms    110.61ms      1.13ms    70.00%
req/s           :     320.63      333.88      325.14        4.94    80.00%
```

