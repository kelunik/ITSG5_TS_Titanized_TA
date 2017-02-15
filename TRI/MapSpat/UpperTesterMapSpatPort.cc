// This Test Port skeleton source file was generated by the
// TTCN-3 Compiler of the TTCN-3 Test Executor version CRL 113 200/5 R3A
// for Lenard Nagy (elnrnag@elx1pjld12-hz) on Fri Dec 11 09:09:35 2015

// Copyright Ericsson Telecom AB 2000-2014

// You may modify this file. Complete the body of empty functions and
// add your member functions here.

#include "UpperTesterMapSpatPort.hh"

namespace LibItsMapSpat__TestSystem {

UpperTesterMapSpatPort::UpperTesterMapSpatPort(const char *par_port_name)
	: UpperTesterMapSpatPort_BASE(par_port_name)
{

}

UpperTesterMapSpatPort::~UpperTesterMapSpatPort()
{

}

void UpperTesterMapSpatPort::set_parameter(const char * parameter_name,
	const char * parameter_value)
{
  TRI_set_param(parameter_name,parameter_value,mp_data);
}

/*void UpperTesterMapSpatPort::Handle_Fd_Event(int fd, boolean is_readable,
	boolean is_writable, boolean is_error) {}*/

void UpperTesterMapSpatPort::Handle_Fd_Event_Error(int fd)
{
  Handle_Fd_Event_Readable(fd);
}

void UpperTesterMapSpatPort::Handle_Fd_Event_Writable(int /*fd*/)
{

}

void UpperTesterMapSpatPort::Handle_Fd_Event_Readable(int fd)
{
  int res=TRI__interface__Types::TRI_read_socket(fd,mp_data.buff);
 
    if(res<=0){
      TTCN_error("TRI_Mapper connection lost");
    }
 
    TRI__interface__Types::TRI__mapper__PDU pdu;
 
    while(TRI__interface__Types::TRI_get_message(mp_data.buff,pdu)){
      switch(pdu.msg().get_selection()){
      case TRI__interface__Types::Msg__union::ALT_enqueue__msg:{
	/**** ****/
	// put the decoder here
	//         incoming_message(data);
	const OCTETSTRING tmp=(const OCTETSTRING)pdu.msg().enqueue__msg().data().encoded__data();
	const unsigned char* tmp1 = (const unsigned char*)tmp;
	if (tmp1[0] == 0x01) { //utInitializeResult
	  if (tmp.lengthof()==2) { //Fixed length 2 octets
	    //Subtract header
	    tmp1++;
	    LibItsCommon__TypesAndValues::UtInitializeResult ret_val;
	    ret_val.utInitializeResult() = *tmp1;
	    incoming_message(ret_val);
	  } else {
	    TTCN_error("Invalid message length of UtInitializeResult");
	  }
	} else if (tmp1[0] == 0xA1) { //utMapSpatTriggerResult
	  if (tmp.lengthof()==2) { //Fixed length 2 octets
	    //Subtract header
	    tmp1++;
	    LibItsMapSpat__TypesAndValues::UtMapSpatTriggerResult ret_val;
	    ret_val.result()   = tmp1[0];
	    ret_val.msgCount() = tmp1[1];
	    incoming_message(ret_val);
	  } else {
	    TTCN_error("Invalid message length of UtMapSpatTriggerResult");
	  }
	} else if (tmp1[0] == 0xA2) {  //UtSpatInd
	  LibItsMapSpat__TypesAndValues::UtMapEventInd ret_val;

	  ret_val = TTCN__EncDec::f__dec__Ut__Map__EventInd(OCTETSTRING(tmp.lengthof()-1,tmp1+1));

	  incoming_message(ret_val);
	} else if (tmp1[0] == 0xA3) { //UtSpatInd
	    if (tmp.lengthof()==2) { //Fixed length 2 octets
	    //Subtract header
	    tmp1++;
	    LibItsMapSpat__TypesAndValues::UtSpatEventInd ret_val;
	    ret_val = TTCN__EncDec::f__dec__Ut__Spat__EventInd(OCTETSTRING(tmp.lengthof()-1,tmp1+1));
	    incoming_message(ret_val);
	  } else {
	    TTCN_error("Invalid message length of UtChangePositionResult");
	  }
	} else if (tmp1[0] == 0x55) {
	  TTCN_Logger::begin_event(TTCN_DEBUG);
	  TTCN_Logger::log_event_str("*** UtGnEventIndication discarded ***");
	  TTCN_Logger::end_event();
	}
	else if (tmp1[0] == 0x63) {
	  TTCN_Logger::begin_event(TTCN_DEBUG);
	  TTCN_Logger::log_event_str("*** UtBtpEventIndication discarded ***");
	  TTCN_Logger::end_event();
	}
	else if (tmp1[0] == 0x13) {
	  TTCN_Logger::begin_event(TTCN_DEBUG);
	  TTCN_Logger::log_event_str("*** UtDenmEventIndication discarded ***");
	  TTCN_Logger::end_event();
	}      
	else if (tmp1[0] == 0x23) {
	  TTCN_Logger::begin_event(TTCN_DEBUG);
	  TTCN_Logger::log_event_str("*** UtCamEventIndication discarded ***");
	  TTCN_Logger::end_event();
	}      
	else if (tmp1[0] == 0x83) {
	  TTCN_Logger::begin_event(TTCN_DEBUG);
	  TTCN_Logger::log_event_str("*** UtGn6EventIndication discarded ***");
	  TTCN_Logger::end_event();
	} else {
	  TTCN_error("Unexpected message");
	}
      }
          
	/**** ****/
	break;
      case TRI__interface__Types::Msg__union::ALT_result:
	if(pdu.msg().result().result()==TRI__interface__Types::Result__value::TRI__error){
	  TTCN_error("Unsucessfull send");
	}
	break;
      default:
	TTCN_error("Unexpected message");
	break;
      }
    }
  }



/*void UpperTesterMapSpatPort::Handle_Timeout(double time_since_last_call) {}*/

void UpperTesterMapSpatPort::user_map(const char * system_port)
{
TRI_map("UtMapSpatPort",system_port,mp_data);
    Handler_Add_Fd_Read(mp_data.tri_socket);
}

void UpperTesterMapSpatPort::user_unmap(const char * system_port)
{
  TRI_unmap(mp_data);
    Uninstall_Handler();
}

void UpperTesterMapSpatPort::user_start()
{
  TRI_start("UtMapSpatPort",get_name(),(component)self,COMPONENT::get_component_name(self),mp_data);
}

void UpperTesterMapSpatPort::user_stop()
{
  TRI_stop(mp_data);
}

void UpperTesterMapSpatPort::outgoing_send(const LibItsCommon__TypesAndValues::UtInitialize& send_par)
{
  TTCN_Buffer sb;

    /**** ****/
    // put the encoder here
    unsigned int header = 0x00;
    sb.put_c(header);
    sb.put_os(send_par.hashedId8());

    /**** ****/
    TRI__interface__Types::TRI__mapper__PDU pdu;

    pdu.msg().sendmsg().addr()=OMIT_VALUE;
    sb.get_string(pdu.msg().sendmsg().data().encoded__data());

    pdu.msg__id()=mp_data.msg_seq_num;
    mp_data.msg_seq_num++;
 
    TRI__interface__Types::TRI_send(mp_data.tri_socket,pdu);
}

void UpperTesterMapSpatPort::outgoing_send(const LibItsMapSpat__TypesAndValues::UtMapSpatTrigger& send_par)
{
    TRI__interface__Types::TRI__mapper__PDU pdu;
    
    /**** ****/
    // put the encoder here
    TTCN_Buffer sb;

    sb.put_c(0xA0);                      //UtMapSpatTrigger message type 
    sb.put_c(send_par.event().as_int());    

    //put into the TRI message
    sb.get_string(pdu.msg().sendmsg().data().encoded__data());
    /**** ****/
 
    pdu.msg().sendmsg().addr()=OMIT_VALUE;
 
    pdu.msg__id()=mp_data.msg_seq_num;
    mp_data.msg_seq_num++;
 
    TRI__interface__Types::TRI_send(mp_data.tri_socket,pdu);
}

} /* end of namespace */

