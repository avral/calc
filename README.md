# Create concract account
```
cleos create account eosio calc EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
```

# Build & deploy
```
make build deploy
```

# Run
```
cleos push action calc calculate '[2]' -p calc

#          calc <= calc::calculate              {"x":2}
>> Result: 16
```
