#pragma once

#include <QObject>
#include <QByteArray>
#include <QSharedPointer>

#include "QJsonChannelMessage.h"

class QJsonChannelServicePrivate;

/**
 * @brief Service wrapper over QOblect is responsible for QObjects methods ivocation according to JSON-RPC requests messages.
 * 
 */
class QJSONCHANNELCORE_EXPORT QJsonChannelService {
public:
    /**
     * @brief Construct a new QJsonChannelService object
     * 
     * @param name Service name
     * @param version Service version
     * @param description Service description
     * @param serviceObjIsThreadSafe Is the service object thread safe
     * @param obj Service object
     */
    QJsonChannelService (const QByteArray& name, const QByteArray& version, const QByteArray& description, QSharedPointer<QObject> obj,
                         bool serviceObjIsThreadSafe);
    ~QJsonChannelService ();

    /**
     * @brief Returns service object
     * 
     * @return QSharedPointer<QObject> 
     */
    QSharedPointer<QObject> serviceObj ();

    /**
     * @brief Returns service name
     * 
     * @return const QByteArray& 
     */
    const QByteArray& serviceName () const;

    /**
     * @brief Returns JSON Document contains JSON Schema Service Descriptor 
     * (https://jsonrpc.org/historical/json-schema-service-descriptor.html)
     * 
     * @return const QJsonObject& 
     */
    const QJsonObject& serviceInfo () const;

    /**
     * @brief Process a JSON-RPC message. In general it means the invocation of a requested function.
     * 
     * @param message JSON-RPC message
     * @return QJsonChannelMessage JSON-RPC response message
     */
    QJsonChannelMessage dispatch (const QJsonChannelMessage& request) const;

private:
    Q_DISABLE_COPY (QJsonChannelService)
    Q_DECLARE_PRIVATE (QJsonChannelService)

#if !defined(USE_QT_PRIVATE_HEADERS)
    QScopedPointer<QJsonChannelServicePrivate> d_ptr;
#endif
};
