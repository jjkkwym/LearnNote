# issus

## github push commit fail

fatal: unable to access 'https://github.com/jjkkwym/code.git/': GnuTLS recv error (-110): The TLS connection was non-properly terminated.

取消git本身的https代理，使用自己本机的代理
git config --global --unset http.proxy
git config --global --unset https.proxy