cleos_path=cleos
source_path=$(PWD)
contract=calc

build:
	eosio-cpp -w -I ./ --abigen $(source_path)/$(contract).cpp -o $(source_path)/$(contract).wasm

deploy:
	$(cleos_path) set contract $(contract) $(source_path) $(contract).wasm $(contract).abi -p $(contract)@active
	$(cleos_path) set account permission $(contract) active --add-code
