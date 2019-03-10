#pragma once

#include <QScopedPointer>

#include "QJsonChannelGlobal.h"

class QJsonChannelMessage;
class QJsonChannelService;
class QJsonChannelServiceRepositoryPrivate;

/**
 * @brief The main entity of QJsonChannel represents service repository and provides API for a JSON-RPC method invokation.
 * 
 */
class QJSONCHANNELCORE_EXPORT QJsonChannelServiceRepository {
public:
    QJsonChannelServiceRepository ();
    ~QJsonChannelServiceRepository ();

     /**
      * @brief Adds service to the repository
      * 
      * @param service A service to attach to the repository
      * @return true in case the sevice was added
      * @return false in case of failure
      */
     bool addService (const QSharedPointer <QJsonChannelService>& service);
    
    /**
     * @brief Adds service to the repository
     * 
     * @param name Service name
     * @param version Service version
     * @param description Service description
     * @param obj Service object
     * @return true In case the sevice was added
     * @return false In case of failure
     */
    bool addService (const QByteArray& name, const QByteArray& version, const QByteArray& description, QSharedPointer<QObject> obj);

	/**
	* @brief Adds thread-safe service to the repository. Service will be not locker during the methods invocation.
	*
	* @param name Service name
	* @param version Service version
	* @param description Service description
	* @param obj Service object
	* @return true In case the sevice was added
	* @return false In case of failure
	*/
	bool addThreadSafeService(const QByteArray& name, const QByteArray& version, const QByteArray& description, QSharedPointer<QObject> obj);

    /**
     * @brief Return service by name
     * 
     * @param serviceName a service name to search
     * @return QSharedPointer <QJsonChannelService>  a found sevice 
     */
	QSharedPointer <QJsonChannelService> getService (const QByteArray& serviceName);

    /**
     * @brief Return service object by name
     * 
     * @param serviceName a service name to search
     * @return QSharedPointer<QObject> a found sevice 
     */
	QSharedPointer<QObject> getServiceObject (const QByteArray& serviceName);

    /**
     * @brief Removes service from the repository
     * 
     * @param serviceName A service name to remove from the repository
     * @return true in case the sevice was removed
     * @return false in case of failure
     */
    bool removeService (const QByteArray& serviceName);

    /**
     * @brief Process a JSON-RPC message. In general it means the invocation of a requested function of a requested service
     * 
     * @param message JSON-RPC message
     * @return QJsonChannelMessage JSON-RPC response message
     */
    QJsonChannelMessage processMessage (const QJsonChannelMessage& message);

private:
    QScopedPointer<QJsonChannelServiceRepositoryPrivate> d;
};
