#ifndef	__RSP_H__
#define	__RSP_H__

#define	PORT_NUMBER	42001

//message type (2 types)
#define	MSG_TYPE_UPDATE		"sensor-update"
#define	MSG_TYPE_BROADCAST	"broadcast"

//for message type sensor-update
typedef	struct _rspSensor_Update
{
	unsigned char*			Name;
	unsigned char*			Value;
	struct _rspSensor_Update*	Next;
} RSP_Sensor_Value, *pRSP_Sensor_Value;
//for message type broadcast
typedef struct _rspBroadcast
{
	unsigned char*		Name;
	struct _rspBroadcast*	Next;
}RSP_Broadcast_Name, *pRSP_Broadcast_Name;
//for message type (using union)
typedef union _rspList
{
	RSP_Sensor_Value        Value;
	RSP_Broadcast_Name	Broadcast;
}RSP_Message_List, *pRSP_Message_List;


typedef	struct _rspMessage
{
	unsigned int		Size;
	unsigned char*		Message;
	RSP_Message_List	List;
} RSP_Message, *pRPS_Message;


#endif	//__RSP_H__
