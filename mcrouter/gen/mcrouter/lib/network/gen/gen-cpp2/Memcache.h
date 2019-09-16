/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/service_h.h>

#include "mcrouter/lib/network/gen/gen-cpp2/MemcacheAsyncClient.h"
#include "mcrouter/lib/network/gen/gen-cpp2/MemcacheService_types.h"
#include "mcrouter/lib/network/gen/gen-cpp2/Common_types.h"
#include "mcrouter/lib/network/gen/gen-cpp2/Memcache_types.h"
#include "mcrouter/lib/network/gen/MemcacheMessages.h"

namespace folly {
  class IOBuf;
  class IOBufQueue;
}
namespace apache { namespace thrift {
  class Cpp2RequestContext;
  class BinaryProtocolReader;
  class CompactProtocolReader;
  namespace transport { class THeader; }
}}

namespace facebook { namespace memcache { namespace thrift {

class MemcacheSvAsyncIf {
 public:
  virtual ~MemcacheSvAsyncIf() {}
  virtual void async_eb_mcGet(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McGetReply>> callback, const facebook::memcache::McGetRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McGetReply> future_mcGet(const facebook::memcache::McGetRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McGetReply> semifuture_mcGet(const facebook::memcache::McGetRequest& request) = 0;
  virtual void async_eb_mcSet(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McSetReply>> callback, const facebook::memcache::McSetRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McSetReply> future_mcSet(const facebook::memcache::McSetRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McSetReply> semifuture_mcSet(const facebook::memcache::McSetRequest& request) = 0;
  virtual void async_eb_mcDelete(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McDeleteReply>> callback, const facebook::memcache::McDeleteRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McDeleteReply> future_mcDelete(const facebook::memcache::McDeleteRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McDeleteReply> semifuture_mcDelete(const facebook::memcache::McDeleteRequest& request) = 0;
  virtual void async_eb_mcLeaseGet(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McLeaseGetReply>> callback, const facebook::memcache::McLeaseGetRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McLeaseGetReply> future_mcLeaseGet(const facebook::memcache::McLeaseGetRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McLeaseGetReply> semifuture_mcLeaseGet(const facebook::memcache::McLeaseGetRequest& request) = 0;
  virtual void async_eb_mcLeaseSet(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McLeaseSetReply>> callback, const facebook::memcache::McLeaseSetRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McLeaseSetReply> future_mcLeaseSet(const facebook::memcache::McLeaseSetRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McLeaseSetReply> semifuture_mcLeaseSet(const facebook::memcache::McLeaseSetRequest& request) = 0;
  virtual void async_eb_mcAdd(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McAddReply>> callback, const facebook::memcache::McAddRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McAddReply> future_mcAdd(const facebook::memcache::McAddRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McAddReply> semifuture_mcAdd(const facebook::memcache::McAddRequest& request) = 0;
  virtual void async_eb_mcReplace(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McReplaceReply>> callback, const facebook::memcache::McReplaceRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McReplaceReply> future_mcReplace(const facebook::memcache::McReplaceRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McReplaceReply> semifuture_mcReplace(const facebook::memcache::McReplaceRequest& request) = 0;
  virtual void async_eb_mcGets(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McGetsReply>> callback, const facebook::memcache::McGetsRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McGetsReply> future_mcGets(const facebook::memcache::McGetsRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McGetsReply> semifuture_mcGets(const facebook::memcache::McGetsRequest& request) = 0;
  virtual void async_eb_mcCas(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McCasReply>> callback, const facebook::memcache::McCasRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McCasReply> future_mcCas(const facebook::memcache::McCasRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McCasReply> semifuture_mcCas(const facebook::memcache::McCasRequest& request) = 0;
  virtual void async_eb_mcIncr(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McIncrReply>> callback, const facebook::memcache::McIncrRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McIncrReply> future_mcIncr(const facebook::memcache::McIncrRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McIncrReply> semifuture_mcIncr(const facebook::memcache::McIncrRequest& request) = 0;
  virtual void async_eb_mcDecr(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McDecrReply>> callback, const facebook::memcache::McDecrRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McDecrReply> future_mcDecr(const facebook::memcache::McDecrRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McDecrReply> semifuture_mcDecr(const facebook::memcache::McDecrRequest& request) = 0;
  virtual void async_eb_mcMetaget(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McMetagetReply>> callback, const facebook::memcache::McMetagetRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McMetagetReply> future_mcMetaget(const facebook::memcache::McMetagetRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McMetagetReply> semifuture_mcMetaget(const facebook::memcache::McMetagetRequest& request) = 0;
  virtual void async_eb_mcAppend(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McAppendReply>> callback, const facebook::memcache::McAppendRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McAppendReply> future_mcAppend(const facebook::memcache::McAppendRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McAppendReply> semifuture_mcAppend(const facebook::memcache::McAppendRequest& request) = 0;
  virtual void async_eb_mcPrepend(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McPrependReply>> callback, const facebook::memcache::McPrependRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McPrependReply> future_mcPrepend(const facebook::memcache::McPrependRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McPrependReply> semifuture_mcPrepend(const facebook::memcache::McPrependRequest& request) = 0;
  virtual void async_eb_mcTouch(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McTouchReply>> callback, const facebook::memcache::McTouchRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McTouchReply> future_mcTouch(const facebook::memcache::McTouchRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McTouchReply> semifuture_mcTouch(const facebook::memcache::McTouchRequest& request) = 0;
  virtual void async_eb_mcFlushRe(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McFlushReReply>> callback, const facebook::memcache::McFlushReRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McFlushReReply> future_mcFlushRe(const facebook::memcache::McFlushReRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McFlushReReply> semifuture_mcFlushRe(const facebook::memcache::McFlushReRequest& request) = 0;
  virtual void async_eb_mcFlushAll(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McFlushAllReply>> callback, const facebook::memcache::McFlushAllRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McFlushAllReply> future_mcFlushAll(const facebook::memcache::McFlushAllRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McFlushAllReply> semifuture_mcFlushAll(const facebook::memcache::McFlushAllRequest& request) = 0;
  virtual void async_eb_mcGat(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McGatReply>> callback, const facebook::memcache::McGatRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McGatReply> future_mcGat(const facebook::memcache::McGatRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McGatReply> semifuture_mcGat(const facebook::memcache::McGatRequest& request) = 0;
  virtual void async_eb_mcGats(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McGatsReply>> callback, const facebook::memcache::McGatsRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McGatsReply> future_mcGats(const facebook::memcache::McGatsRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McGatsReply> semifuture_mcGats(const facebook::memcache::McGatsRequest& request) = 0;
  virtual void async_eb_mcVersion(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McVersionReply>> callback, const facebook::memcache::McVersionRequest& request) = 0;
  virtual folly::Future<facebook::memcache::McVersionReply> future_mcVersion(const facebook::memcache::McVersionRequest& request) = 0;
  virtual folly::SemiFuture<facebook::memcache::McVersionReply> semifuture_mcVersion(const facebook::memcache::McVersionRequest& request) = 0;
};

class MemcacheAsyncProcessor;

class MemcacheSvIf : public MemcacheSvAsyncIf, public apache::thrift::ServerInterface {
 public:
  typedef MemcacheAsyncProcessor ProcessorType;
  std::unique_ptr<apache::thrift::AsyncProcessor> getProcessor() override;
  virtual void mcGet(facebook::memcache::McGetReply& /*_return*/, const facebook::memcache::McGetRequest& /*request*/);
  folly::Future<facebook::memcache::McGetReply> future_mcGet(const facebook::memcache::McGetRequest& request) override;
  folly::SemiFuture<facebook::memcache::McGetReply> semifuture_mcGet(const facebook::memcache::McGetRequest& request) override;
  void async_eb_mcGet(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McGetReply>> callback, const facebook::memcache::McGetRequest& request) override;
  virtual void mcSet(facebook::memcache::McSetReply& /*_return*/, const facebook::memcache::McSetRequest& /*request*/);
  folly::Future<facebook::memcache::McSetReply> future_mcSet(const facebook::memcache::McSetRequest& request) override;
  folly::SemiFuture<facebook::memcache::McSetReply> semifuture_mcSet(const facebook::memcache::McSetRequest& request) override;
  void async_eb_mcSet(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McSetReply>> callback, const facebook::memcache::McSetRequest& request) override;
  virtual void mcDelete(facebook::memcache::McDeleteReply& /*_return*/, const facebook::memcache::McDeleteRequest& /*request*/);
  folly::Future<facebook::memcache::McDeleteReply> future_mcDelete(const facebook::memcache::McDeleteRequest& request) override;
  folly::SemiFuture<facebook::memcache::McDeleteReply> semifuture_mcDelete(const facebook::memcache::McDeleteRequest& request) override;
  void async_eb_mcDelete(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McDeleteReply>> callback, const facebook::memcache::McDeleteRequest& request) override;
  virtual void mcLeaseGet(facebook::memcache::McLeaseGetReply& /*_return*/, const facebook::memcache::McLeaseGetRequest& /*request*/);
  folly::Future<facebook::memcache::McLeaseGetReply> future_mcLeaseGet(const facebook::memcache::McLeaseGetRequest& request) override;
  folly::SemiFuture<facebook::memcache::McLeaseGetReply> semifuture_mcLeaseGet(const facebook::memcache::McLeaseGetRequest& request) override;
  void async_eb_mcLeaseGet(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McLeaseGetReply>> callback, const facebook::memcache::McLeaseGetRequest& request) override;
  virtual void mcLeaseSet(facebook::memcache::McLeaseSetReply& /*_return*/, const facebook::memcache::McLeaseSetRequest& /*request*/);
  folly::Future<facebook::memcache::McLeaseSetReply> future_mcLeaseSet(const facebook::memcache::McLeaseSetRequest& request) override;
  folly::SemiFuture<facebook::memcache::McLeaseSetReply> semifuture_mcLeaseSet(const facebook::memcache::McLeaseSetRequest& request) override;
  void async_eb_mcLeaseSet(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McLeaseSetReply>> callback, const facebook::memcache::McLeaseSetRequest& request) override;
  virtual void mcAdd(facebook::memcache::McAddReply& /*_return*/, const facebook::memcache::McAddRequest& /*request*/);
  folly::Future<facebook::memcache::McAddReply> future_mcAdd(const facebook::memcache::McAddRequest& request) override;
  folly::SemiFuture<facebook::memcache::McAddReply> semifuture_mcAdd(const facebook::memcache::McAddRequest& request) override;
  void async_eb_mcAdd(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McAddReply>> callback, const facebook::memcache::McAddRequest& request) override;
  virtual void mcReplace(facebook::memcache::McReplaceReply& /*_return*/, const facebook::memcache::McReplaceRequest& /*request*/);
  folly::Future<facebook::memcache::McReplaceReply> future_mcReplace(const facebook::memcache::McReplaceRequest& request) override;
  folly::SemiFuture<facebook::memcache::McReplaceReply> semifuture_mcReplace(const facebook::memcache::McReplaceRequest& request) override;
  void async_eb_mcReplace(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McReplaceReply>> callback, const facebook::memcache::McReplaceRequest& request) override;
  virtual void mcGets(facebook::memcache::McGetsReply& /*_return*/, const facebook::memcache::McGetsRequest& /*request*/);
  folly::Future<facebook::memcache::McGetsReply> future_mcGets(const facebook::memcache::McGetsRequest& request) override;
  folly::SemiFuture<facebook::memcache::McGetsReply> semifuture_mcGets(const facebook::memcache::McGetsRequest& request) override;
  void async_eb_mcGets(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McGetsReply>> callback, const facebook::memcache::McGetsRequest& request) override;
  virtual void mcCas(facebook::memcache::McCasReply& /*_return*/, const facebook::memcache::McCasRequest& /*request*/);
  folly::Future<facebook::memcache::McCasReply> future_mcCas(const facebook::memcache::McCasRequest& request) override;
  folly::SemiFuture<facebook::memcache::McCasReply> semifuture_mcCas(const facebook::memcache::McCasRequest& request) override;
  void async_eb_mcCas(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McCasReply>> callback, const facebook::memcache::McCasRequest& request) override;
  virtual void mcIncr(facebook::memcache::McIncrReply& /*_return*/, const facebook::memcache::McIncrRequest& /*request*/);
  folly::Future<facebook::memcache::McIncrReply> future_mcIncr(const facebook::memcache::McIncrRequest& request) override;
  folly::SemiFuture<facebook::memcache::McIncrReply> semifuture_mcIncr(const facebook::memcache::McIncrRequest& request) override;
  void async_eb_mcIncr(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McIncrReply>> callback, const facebook::memcache::McIncrRequest& request) override;
  virtual void mcDecr(facebook::memcache::McDecrReply& /*_return*/, const facebook::memcache::McDecrRequest& /*request*/);
  folly::Future<facebook::memcache::McDecrReply> future_mcDecr(const facebook::memcache::McDecrRequest& request) override;
  folly::SemiFuture<facebook::memcache::McDecrReply> semifuture_mcDecr(const facebook::memcache::McDecrRequest& request) override;
  void async_eb_mcDecr(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McDecrReply>> callback, const facebook::memcache::McDecrRequest& request) override;
  virtual void mcMetaget(facebook::memcache::McMetagetReply& /*_return*/, const facebook::memcache::McMetagetRequest& /*request*/);
  folly::Future<facebook::memcache::McMetagetReply> future_mcMetaget(const facebook::memcache::McMetagetRequest& request) override;
  folly::SemiFuture<facebook::memcache::McMetagetReply> semifuture_mcMetaget(const facebook::memcache::McMetagetRequest& request) override;
  void async_eb_mcMetaget(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McMetagetReply>> callback, const facebook::memcache::McMetagetRequest& request) override;
  virtual void mcAppend(facebook::memcache::McAppendReply& /*_return*/, const facebook::memcache::McAppendRequest& /*request*/);
  folly::Future<facebook::memcache::McAppendReply> future_mcAppend(const facebook::memcache::McAppendRequest& request) override;
  folly::SemiFuture<facebook::memcache::McAppendReply> semifuture_mcAppend(const facebook::memcache::McAppendRequest& request) override;
  void async_eb_mcAppend(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McAppendReply>> callback, const facebook::memcache::McAppendRequest& request) override;
  virtual void mcPrepend(facebook::memcache::McPrependReply& /*_return*/, const facebook::memcache::McPrependRequest& /*request*/);
  folly::Future<facebook::memcache::McPrependReply> future_mcPrepend(const facebook::memcache::McPrependRequest& request) override;
  folly::SemiFuture<facebook::memcache::McPrependReply> semifuture_mcPrepend(const facebook::memcache::McPrependRequest& request) override;
  void async_eb_mcPrepend(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McPrependReply>> callback, const facebook::memcache::McPrependRequest& request) override;
  virtual void mcTouch(facebook::memcache::McTouchReply& /*_return*/, const facebook::memcache::McTouchRequest& /*request*/);
  folly::Future<facebook::memcache::McTouchReply> future_mcTouch(const facebook::memcache::McTouchRequest& request) override;
  folly::SemiFuture<facebook::memcache::McTouchReply> semifuture_mcTouch(const facebook::memcache::McTouchRequest& request) override;
  void async_eb_mcTouch(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McTouchReply>> callback, const facebook::memcache::McTouchRequest& request) override;
  virtual void mcFlushRe(facebook::memcache::McFlushReReply& /*_return*/, const facebook::memcache::McFlushReRequest& /*request*/);
  folly::Future<facebook::memcache::McFlushReReply> future_mcFlushRe(const facebook::memcache::McFlushReRequest& request) override;
  folly::SemiFuture<facebook::memcache::McFlushReReply> semifuture_mcFlushRe(const facebook::memcache::McFlushReRequest& request) override;
  void async_eb_mcFlushRe(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McFlushReReply>> callback, const facebook::memcache::McFlushReRequest& request) override;
  virtual void mcFlushAll(facebook::memcache::McFlushAllReply& /*_return*/, const facebook::memcache::McFlushAllRequest& /*request*/);
  folly::Future<facebook::memcache::McFlushAllReply> future_mcFlushAll(const facebook::memcache::McFlushAllRequest& request) override;
  folly::SemiFuture<facebook::memcache::McFlushAllReply> semifuture_mcFlushAll(const facebook::memcache::McFlushAllRequest& request) override;
  void async_eb_mcFlushAll(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McFlushAllReply>> callback, const facebook::memcache::McFlushAllRequest& request) override;
  virtual void mcGat(facebook::memcache::McGatReply& /*_return*/, const facebook::memcache::McGatRequest& /*request*/);
  folly::Future<facebook::memcache::McGatReply> future_mcGat(const facebook::memcache::McGatRequest& request) override;
  folly::SemiFuture<facebook::memcache::McGatReply> semifuture_mcGat(const facebook::memcache::McGatRequest& request) override;
  void async_eb_mcGat(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McGatReply>> callback, const facebook::memcache::McGatRequest& request) override;
  virtual void mcGats(facebook::memcache::McGatsReply& /*_return*/, const facebook::memcache::McGatsRequest& /*request*/);
  folly::Future<facebook::memcache::McGatsReply> future_mcGats(const facebook::memcache::McGatsRequest& request) override;
  folly::SemiFuture<facebook::memcache::McGatsReply> semifuture_mcGats(const facebook::memcache::McGatsRequest& request) override;
  void async_eb_mcGats(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McGatsReply>> callback, const facebook::memcache::McGatsRequest& request) override;
  virtual void mcVersion(facebook::memcache::McVersionReply& /*_return*/, const facebook::memcache::McVersionRequest& /*request*/);
  folly::Future<facebook::memcache::McVersionReply> future_mcVersion(const facebook::memcache::McVersionRequest& request) override;
  folly::SemiFuture<facebook::memcache::McVersionReply> semifuture_mcVersion(const facebook::memcache::McVersionRequest& request) override;
  void async_eb_mcVersion(std::unique_ptr<apache::thrift::HandlerCallback<facebook::memcache::McVersionReply>> callback, const facebook::memcache::McVersionRequest& request) override;
};

class MemcacheSvNull : public MemcacheSvIf {
 public:
};

class MemcacheAsyncProcessor : public ::apache::thrift::GeneratedAsyncProcessor {
 public:
  const char* getServiceName() override;
  using BaseAsyncProcessor = void;
 protected:
  MemcacheSvIf* iface_;
  folly::Optional<std::string> getCacheKey(folly::IOBuf* buf, apache::thrift::protocol::PROTOCOL_TYPES protType) override;
 public:
  void process(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) override;
 protected:
  bool isOnewayMethod(const folly::IOBuf* buf, const apache::thrift::transport::THeader* header) override;
  std::shared_ptr<folly::RequestContext> getBaseContextForRequest() override;
 private:
  static std::unordered_set<std::string> onewayMethods_;
  static std::unordered_map<std::string, int16_t> cacheKeyMap_;
 public:
  using ProcessFunc = GeneratedAsyncProcessor::ProcessFunc<MemcacheAsyncProcessor>;
  using ProcessMap = GeneratedAsyncProcessor::ProcessMap<ProcessFunc>;
  static const MemcacheAsyncProcessor::ProcessMap& getBinaryProtocolProcessMap();
  static const MemcacheAsyncProcessor::ProcessMap& getCompactProtocolProcessMap();
 private:
  static const MemcacheAsyncProcessor::ProcessMap binaryProcessMap_;
   static const MemcacheAsyncProcessor::ProcessMap compactProcessMap_;
 private:
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcGet(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcGet(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McGetReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcGet(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcSet(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcSet(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McSetReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcSet(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcDelete(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcDelete(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McDeleteReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcDelete(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcLeaseGet(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcLeaseGet(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McLeaseGetReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcLeaseGet(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcLeaseSet(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcLeaseSet(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McLeaseSetReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcLeaseSet(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcAdd(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcAdd(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McAddReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcAdd(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcReplace(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcReplace(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McReplaceReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcReplace(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcGets(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcGets(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McGetsReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcGets(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcCas(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcCas(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McCasReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcCas(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcIncr(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcIncr(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McIncrReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcIncr(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcDecr(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcDecr(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McDecrReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcDecr(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcMetaget(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcMetaget(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McMetagetReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcMetaget(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcAppend(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcAppend(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McAppendReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcAppend(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcPrepend(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcPrepend(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McPrependReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcPrepend(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcTouch(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcTouch(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McTouchReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcTouch(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcFlushRe(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcFlushRe(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McFlushReReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcFlushRe(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcFlushAll(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcFlushAll(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McFlushAllReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcFlushAll(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcGat(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcGat(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McGatReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcGat(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcGats(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcGats(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McGatsReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcGats(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_mcVersion(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf,apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static folly::IOBufQueue return_mcVersion(int32_t protoSeqId, apache::thrift::ContextStack* ctx, facebook::memcache::McVersionReply const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_mcVersion(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
 public:
  MemcacheAsyncProcessor(MemcacheSvIf* iface) :
      iface_(iface) {}

  virtual ~MemcacheAsyncProcessor() {}
};

}}} // facebook::memcache::thrift
namespace apache { namespace thrift {

}} // apache::thrift
