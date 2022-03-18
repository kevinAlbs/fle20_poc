To start mongod or mongocryptd with FLE 2 support, use the `--setParameter featureFlagFLE2=1`.

```
mlaunch --replicaset --nodes 1 --binarypath $(m bin dev) --setParameter 
enableTestCommands=1 --setParameter featureFlagFLE2=1 --dir .menv
```

--

This repository is for POC and notes of FLE 2.0 support in drivers.

For POC of API in Go, see https://github.com/kevinAlbs/mongo-go-driver/tree/fle20_poc

For POC of work in libmongocrypt, see https://github.com/kevinAlbs/libmongocrypt/tree/fle20_poc