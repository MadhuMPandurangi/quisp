#include "RuleSetStore.h"
namespace quisp::modules::ruleset_store {

int RuleSetStore::size() { return rulesets.size(); }

RuleSetVector::const_iterator RuleSetStore::cbegin() { return rulesets.cbegin(); }
RuleSetVector::const_iterator RuleSetStore::cend() { return rulesets.cend(); }
RuleSetVector::iterator RuleSetStore::begin() { return rulesets.begin(); }
RuleSetVector::iterator RuleSetStore::end() { return rulesets.end(); }

void RuleSetStore::insert(std::unique_ptr<RuleSet>& ruleset) { rulesets.emplace_back(std::move(ruleset)); }
void RuleSetStore::insert(RuleSet* ruleset) { rulesets.emplace_back(std::unique_ptr<RuleSet>(ruleset)); }
void RuleSetStore::erase(const RuleSetVector::const_iterator& ruleset) { rulesets.erase(ruleset); }
std::unique_ptr<RuleSet>& RuleSetStore::operator[](int i) { return rulesets[i]; }

}  // namespace quisp::modules::ruleset_store
