#ifndef KAFKAPRODUCER_H
#define KAFKAPRODUCER_H

#include "cppkafka/configuration.h"
#include "cppkafka/producer.h"
#include <cppkafka/message_builder.h>
#include <memory>

using cppkafka::Configuration;
using cppkafka::MessageBuilder;
using cppkafka::Producer;
using cppkafka::Topic;

class KafkaProducer
{
public:
    static KafkaProducer* instance()
    {
        static std::unique_ptr<KafkaProducer> instance;

        if (!instance) {
            instance.reset(new KafkaProducer());
        }

        return instance.get();
    }

    void produce(const std::string& id, const std::string& payload);

private:
    KafkaProducer();
    Configuration m_config;
    std::unique_ptr<Producer> m_producer;
    bool m_isReady = false;
};

#endif // KAFKAPRODUCER_H
