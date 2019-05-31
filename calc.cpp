#include <eosiolib/eosio.hpp>

using namespace eosio;


class [[eosio::contract]] calc : public eosio::contract {
   using contract::contract;

   public:
      calc(name receiver, name code, datastream<const char*> ds)
         :contract(receiver, code, ds),
         _results(receiver, receiver.value){};

      [[eosio::action]]
      void calculate(const uint64_t x) {
         uint64_t result = x * 8;
         
         _results.emplace(_self, [&]( auto& r ) {
            r.id = _results.available_primary_key();
            r.result = result;
         });

         print("Result: " + std::to_string(result));
      };
   private:
      struct [[eosio::contract]] result {
         uint64_t id;
         uint64_t result;

         uint64_t primary_key() const { return id; }
      };
   
      typedef eosio::multi_index<"results"_n, result> results;

      results _results;
};


extern "C" {
  void apply(uint64_t receiver, uint64_t code, uint64_t action) {
    if(code==receiver && action=="calculate"_n.value) {
      execute_action(name(receiver), name(code), &calc::calculate);
    }
  }
}
