#pragma once

#include <QSharedDataPointer>
#include <QMetaType>

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include "QJsonChannelGlobal.h"

class QJsonChannelMessagePrivate;
class QJSONCHANNELCORE_EXPORT QJsonChannelMessage {
public:
    QJsonChannelMessage ();
    QJsonChannelMessage (const QJsonChannelMessage& other);
    QJsonChannelMessage& operator= (const QJsonChannelMessage& other);
    ~QJsonChannelMessage ();

    inline void swap (QJsonChannelMessage& other) {
        qSwap (d, other.d);
    }

    /**
     * @brief Message types
     * 
     */
    enum Type { 
        //! Invalid message
        Invalid, 
        //! Request message
        Request, 
        //! Response message
        Response, 
        //! Notification message
        Notification, 
        //! Error Response message
        Error, 
        //! Discrovery Request message
        Discrovery 
        };

    /**
     * @brief Create a Request for a positional method call
     * 
     * @param method Method name
     * @param params Arguments values array 
     * @return QJsonChannelMessage 
     */
    static QJsonChannelMessage createRequest (const QString& method, const QJsonArray& params = QJsonArray ());
    /**
     * @brief Create a Request for a single argument method call
     * 
     * @param method Method name
     * @param param Argument value
     * @return QJsonChannelMessage 
     */
    static QJsonChannelMessage createRequest (const QString& method, const QJsonValue& param);
    /**
     * @brief Create a Request for a name method call
     * 
     * @param method Method name
     * @param params Arguments names and values as JSON object
     * @return QJsonChannelMessage 
     */
    static QJsonChannelMessage createRequest (const QString& method, const QJsonObject& namedParameters);

    /**
     * @brief Create a Notification for a positional method call
     * 
     * @param method Method name
     * @param params Arguments values array 
     * @return QJsonChannelMessage 
     */
    static QJsonChannelMessage createNotification (const QString& method, const QJsonArray& params = QJsonArray ());
    /**
     * @brief Create a Notification for a single argument method call
     * 
     * @param method Method name
     * @param param Argument value
     * @return QJsonChannelMessage 
     */
    static QJsonChannelMessage createNotification (const QString& method, const QJsonValue& param);
    /**
     * @brief Create a Notification for a name method call
     * 
     * @param method Method name
     * @param params Arguments names and values as JSON object
     * @return QJsonChannelMessage 
     */
    static QJsonChannelMessage createNotification (const QString& method, const QJsonObject& namedParameters);

    /**
     * @brief Create a Response object
     * 
     * @param result Value of the call result
     * @return QJsonChannelMessage 
     */
    QJsonChannelMessage createResponse (const QJsonValue& result) const;

    /**
     * @brief Create a Error Response object
     * 
     * @param code Error code
     * @param message Error message
     * @param data Associate data
     * @return QJsonChannelMessage 
     */
    QJsonChannelMessage createErrorResponse (QJsonChannel::ErrorCode code, const QString& message = QString (), const QJsonValue& data = QJsonValue ()) const;

    /**
     * @brief Returns message type
     * 
     * @return QJsonChannelMessage::Type 
     */
    QJsonChannelMessage::Type type () const;

    /**
     * @brief Verifies if the message has valid type
     * 
     * @return true If the type is valid
     * @return false If the typie is QJsonChannelMessage::Type::Invalid
     */
    bool                      isValid () const;

    /**
     * @brief Returns message Id
     * 
     * @return int message Id
     */
    int                       id () const;

    // request
    /**
     * @brief Returns requested service name (of Request message)
     * 
     * @return QString 
     */
    QString    serviceName () const;
    /**
     * @brief Returns requested method name (of Request message)
     * 
     * @return QString 
     */
    QString    method () const;
    /**
     * @brief Returns the Request params (of Request message)
     * 
     * @return QJsonValue 
     */
    QJsonValue params () const;

    // response
    /**
     * @brief Returns Response values (of response message)
     * 
     * @return QJsonValue 
     */
    QJsonValue result () const;

    // error
    /**
     * @brief Returns error code (of Error message)
     * 
     * @return int 
     */
    int        errorCode () const;
    /**
     * @brief Returns error message (of Error message)
     * 
     * @return QString 
     */
    QString    errorMessage () const;
    /**
     * @brief Returns error data (of Error message)
     * 
     * @return QJsonValue 
     */
    QJsonValue errorData () const;

    /**
     * @brief Converts the message to JSON object
     * 
     * @return QJsonObject 
     */
    QJsonObject                toObject () const;

    /**
     * @brief Converts a JSON to a JSON-RPC message
     * 
     * @param object 
     * @return QJsonChannelMessage 
     */
    static QJsonChannelMessage fromObject (const QJsonObject& object);

    /**
     * @brief Converts the message to string data
     * 
     * @return QByteArray 
     */
    QByteArray                 toJson () const;
    /**
     * @brief Convert a string data to a JSON-RPC message
     * 
     * @param data String data
     * @return QJsonChannelMessage 
     */
    static QJsonChannelMessage fromJson (const QByteArray& data);

    bool        operator== (const QJsonChannelMessage& message) const;
    inline bool operator!= (const QJsonChannelMessage& message) const {
        return !(operator== (message));
    }

private:
    friend class QJsonChannelMessagePrivate;
    QSharedDataPointer<QJsonChannelMessagePrivate> d;
};

QJSONCHANNELCORE_EXPORT QDebug operator<< (QDebug, const QJsonChannelMessage&);
Q_DECLARE_METATYPE (QJsonChannelMessage)
Q_DECLARE_SHARED (QJsonChannelMessage)
