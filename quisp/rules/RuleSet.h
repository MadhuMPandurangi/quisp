#pragma once
#include <memory>
#include "Rule.h"

namespace quisp::rules {

/**
 * @brief RuleSet class which includes a set of Rule Information
 *
 */
class RuleSet {
 public:
  RuleSet(unsigned long ruleset_id, int owner_address);

  unsigned long ruleset_id;  ///< `ruleset_id` is used for identifying connection
  int owner_addr;  ///< Address of RuleSet owner
  std::vector<std::unique_ptr<Rule>> rules;

  Rule *addRule(std::unique_ptr<Rule> rule, std::vector<int> partners);
  void serialize();
  void deserialize();
  unsigned long createUniqueId();
};

}  // namespace quisp::rules
