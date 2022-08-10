#pragma once

#include <modules/Logger/ILogger.h>
#include <utils/ComponentProvider.h>
#include <memory>
#include <vector>
#include "../QNicRecord/IQNicRecord.h"
#include "../QNicRecord/QNicRecord.h"
#include "IQNicStore.h"

namespace quisp::modules::qnic_store {

using UniqueQNicRecord = std::unique_ptr<quisp::modules::qnic_record::IQNicRecord>;
using QNicRecordType = quisp::modules::qnic_record::QNicRecord;

using QNicIndex = int;

class QNicStore : public IQNicStore {
 public:
  QNicStore(utils::ComponentProvider& provider, int number_of_emitter_qnics, int number_of_receiver_qnics, int number_of_passive_receiver_qnics, Logger::ILogger* logger = nullptr);
  ~QNicStore(){};
  int countNumFreeQubits(QNIC_type type, int qnic_index) override;
  int takeFreeQubitIndex(QNIC_type type, int qnic_index) override;
  void setQubitBusy(QNIC_type type, int qnic_index, int qubit_index, bool is_busy) override;
  qrsa::IQubitRecord* getQubitRecord(QNIC_type type, int qnic_index, int qubit_index) override;

 protected:
  UniqueQNicRecord& getQNic(QNIC_type type, int qnic_index);
  std::map<QNIC_type, std::vector<UniqueQNicRecord>> qnics;
  utils::ComponentProvider& provider;
};

}  // namespace quisp::modules::qnic_store
