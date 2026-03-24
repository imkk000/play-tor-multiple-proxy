# Tor Proxy

## Why?

I want to play tor socks5 and dns server and random circuits, so I have to use reverse proxy to wrap single port into multiple services. I use `nginx` as reverse proxy and forward with tcp streaming mode to `torsocks`, so tor will handle dns, auth, everything. I also use `proxychains` to inject proxy as well.
