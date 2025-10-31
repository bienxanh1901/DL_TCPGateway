#include "KafkaProducer.h"
#include "ConfigParam.h"

KafkaProducer::KafkaProducer()
{
    if (!ConfigParam::instance()->kafkaBrokers().empty()) {
        m_config.set("metadata.broker.list", ConfigParam::instance()->kafkaBrokers());
        m_config.set("sasl.mechanisms", "PLAIN");
        m_config.set("sasl.username", ConfigParam::instance()->kafkaUsername());
        m_config.set("sasl.password", ConfigParam::instance()->kafkaPassword());
        m_config.set("security.protocol", "SASL_PLAINTEXT");
        m_producer = std::make_unique<Producer>(m_config);
        m_isReady = true;
    }
}

void KafkaProducer::produce(const std::string& id, const std::string& payload)
{
    if (m_isReady) {
        MessageBuilder builder(ConfigParam::instance()->kafkaTopic());
        builder.key(id).payload(payload);
        m_producer->produce(builder);
    }
}
