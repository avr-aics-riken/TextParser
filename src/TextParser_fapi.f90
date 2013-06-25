! -*- mode: Fortran -*-
!***************************************************************************!**
!** Copyright (C) 2012 Tokyo University.
!**
!***************************************************************************
!** @file TextParser.f90
!* ここには TextParser ライブラリのFortran用インターフェースが実装されています。


      integer function TP_READ(tp_ptr,file)
        integer*8 tp_ptr
        integer TP_READ_FORT
        external TP_READ_FORT
        character(LEN=*),INTENT(IN) :: file
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
        integer length
!        length=trim_len(file)
        TP_READ = TP_READ_FORT(tp_ptr,trim(file)//NULL)
      
       return

      end function 

      integer function TP_READ_LOCAL(tp_ptr,file)
        integer*8 tp_ptr
        integer TP_READ_FORT
        external TP_READ_FORT
        character(LEN=*),INTENT(IN) :: file
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
        integer length
!        length=trim_len(file)
        TP_READ = TP_READ_LOCAL_FORT(tp_ptr,trim(file)//NULL)
      
       return

      end function 

      integer function TP_WRITE(tp_ptr,file)
      integer*8 tp_ptr
        integer TP_WRITE_FORT
        external TP_WRITE_FORT
        character(LEN=*),INTENT(IN) :: file
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
        integer length
!        length=trim_len(file)
        TP_WRITE = TP_WRITE_FORT(tp_ptr,trim(file)//NULL)
      
       return
       end function 


       integer function TP_REMOVE(tp_ptr)
       integer*8 tp_ptr
        integer TP_REMOVE_FORT
        external TP_REMOVE_FORT

        TP_REMOVE = TP_REMOVE_FORT(tp_ptr)
       
        return
       
       end function 

      integer function TP_GET_NUMBER_OF_LEAVES(tp_ptr,nleaves)
      integer*8 tp_ptr
        integer,intent(out) :: nleaves

        integer TP_GET_NUMBER_OF_LEAVES_FORT
        external TP_GET_NUMBER_OF_LEAVES_FORT
!        write(6,*) 'TP_GET_NUMBER_OF_LEAVES',nleaves
        TP_GET_NUMBER_OF_LEAVES=TP_GET_NUMBER_OF_LEAVES_FORT(tp_ptr,nleaves)
!        write(6,*) 'TP_GET_NUMBER_OF_LEAVES',nleaves
        return

      end function TP_GET_NUMBER_OF_LEAVES

      integer function TP_GET_LABEL(tp_ptr,ileaves,label)
      integer*8 tp_ptr
        integer,intent(in) :: ileaves
        character(len=*),intent(out) ::label
        integer TP_GET_LABEL_FORT
        external TP_GET_LABEL_FORT
        integer ileaves_shift
       
        ileaves_shift=ileaves-1
        TP_GET_LABEL=TP_GET_LABEL_FORT(tp_ptr,ileaves_shift,label)
        
        return

      end function TP_GET_LABEL

      integer function TP_GET_VALUE(tp_ptr,label,value)
      integer*8 tp_ptr
        character(len=*),intent(in) ::label
        character(len=*),intent(out) ::value
        integer TP_GET_VALUE_FORT
        external TP_GET_VALUE_FORT
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
!        write(6,*) 'TP_GET_VALUE label|', trim(label),'|'
!        write(6,*) 'TP_GET_VALUE value|', trim(value),'|'
        TP_GET_VALUE=TP_GET_VALUE_FORT(tp_ptr,trim(label)//NULL,value)
!        write(6,*) 'tp_get_value',TP_GET_VALUE
        
        return

      end function TP_GET_VALUE

      integer function TP_GET_TYPE(tp_ptr,label,value)
      integer*8 tp_ptr
        character(len=*),intent(in) ::label
        character(len=*),intent(out) ::value
        integer TP_GET_TYPE_FORT
        external TP_GET_TYPE_FORT
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)       

        TP_GET_TYPE=TP_GET_TYPE_FORT(tp_ptr,trim(label)//NULL,value)
        
        return

      end function TP_GET_TYPE

      integer*1 function TP_CONVERT_CHAR(tp_ptr,value,ierror)
      integer*8 tp_ptr
       character(len=*),intent(in) :: value
       integer ierror
       integer*1 TP_CONVERT_CHAR_FORT
       external  TP_CONVERT_CHAR_FORT
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)

       TP_CONVERT_CHAR=TP_CONVERT_CHAR_FORT(tp_ptr,trim(value)//NULL,ierror)
       return
      end function TP_CONVERT_CHAR

      integer*2 function TP_CONVERT_SHORT(tp_ptr,value,ierror)
      integer*8 tp_ptr
       character(len=*),intent(in) :: value
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
       integer ierror
       integer*2 TP_CONVERT_SHORT_FORT
       external  TP_CONVERT_SHORT_FORT

       TP_CONVERT_SHORT=TP_CONVERT_SHORT_FORT(tp_ptr,trim(value)//NULL,ierror)
       return
      end function TP_CONVERT_SHORT

      integer function TP_CONVERT_INT(tp_ptr,value,ierror)
      integer*8 tp_ptr
       character(len=*),intent(in) :: value
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
       integer ierror
       integer TP_CONVERT_INT_FORT
       external  TP_CONVERT_INT_FORT

       TP_CONVERT_INT=TP_CONVERT_INT_FORT(tp_ptr,trim(value)//NULL,ierror)
       return
      end function TP_CONVERT_INT

      integer*8 function TP_CONVERT_LONG(tp_ptr,value,ierror)
      integer*8 tp_ptr
       character(len=*),intent(in) :: value
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
       integer*8 ierror
       integer TP_CONVERT_LONG_FORT
       external  TP_CONVERT_LONG_FORT

       TP_CONVERT_LONG=TP_CONVERT_LONG_FORT(tp_ptr,trim(value)//NULL,ierror)
       return
      end function TP_CONVERT_LONG

      integer*8 function TP_CONVERT_LONG_LONG(tp_ptr,value,ierror)
      integer*8 tp_ptr
       character(len=*),intent(in) :: value
        CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
       integer ierror
       integer*8 TP_CONVERT_LONG_LONG_FORT
       external  TP_CONVERT_LONG_LONG_FORT

       TP_CONVERT_LONG_LONG=TP_CONVERT_LONG_LONG_FORT(tp_ptr,trim(value)//NULL,ierror)
       return
      end function TP_CONVERT_LONG_LONG

      real function TP_CONVERT_FLOAT(tp_ptr,value,ierror)
      integer*8 tp_ptr
       character(len=*),intent(in) :: value
       CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
       integer ierror
       real TP_CONVERT_FLOAT_FORT
       external  TP_CONVERT_FLOAT_FORT

       TP_CONVERT_INT=TP_CONVERT_FLOAT_FORT(tp_ptr,trim(value)//NULL,ierror)
       return
      end function TP_CONVERT_FLOAT

      real*8 function TP_CONVERT_DOUBLE(tp_ptr,value,ierror)
      integer*8 tp_ptr
       character(len=*),intent(in) :: value
       CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
       integer ierror
       real*8 TP_CONVERT_DOUBLE_FORT
       external  TP_CONVERT_DOUBLE_FORT

       TP_CONVERT_INT=TP_CONVERT_DOUBLE_FORT(tp_ptr,trim(value)//NULL,ierror)
       return
      end function TP_CONVERT_DOUBLE
      

      logical function TP_CONVERT_LOGICAL(tp_ptr,value,ierror)
      integer*8 tp_ptr
       character(len=*),intent(in) :: value
       CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
       integer ierror
       integer TP_CONVERT_LOGICAL_FORT
       external  TP_CONVERT_LOGICAL_FORT
       integer tmp
       tmp=TP_CONVERT_FLOAT_FORT(tp_ptr,trim(value)//NULL,ierror)
       TP_CONVERT_LOGICAL=.false.
       if(tmp.eq.1) TP_CONVERT_LOGICAL=.true.
       return
      end function TP_CONVERT_LOGICAL

      integer function TP_GET_NUMBER_OF_ELEMENTS(tp_ptr,vector_value,nvec)
      integer*8 tp_ptr
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
      character(len=*),intent(in)::vector_value

      integer TP_GET_NUMBER_OF_ELEMENTS_FORT
      external TP_GET_NUMBER_OF_ELEMENTS_FORT

      TP_GET_NUMBER_OF_ELEMENTS=TP_GET_NUMBER_OF_ELEMENTS_FORT(tp_ptr,trim(vector_value)//NULL,nvec)

      return

      end function TP_GET_NUMBER_OF_ELEMENTS

      integer function TP_GET_ITH_ELEMENT(tp_ptr,vector_value,ivec,velem)
      integer*8 tp_ptr
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
      character(len=*),intent(in)::vector_value
      character(len=*),intent(out)::velem
      integer TP_GET_ITH_ELEMENT_FORT
      external TP_GET_ITH_ELEMENT_FORT
      integer ivec_shift
      ivec_shift=ivec-1
      TP_GET_ITH_ELEMENT=TP_GET_ITH_ELEMENT_FORT(tp_ptr,trim(vector_value)//NULL,ivec_shift,velem)
      return

      end function TP_GET_ITH_ELEMENT

      integer function TP_CURRENT_NODE(tp_ptr,label)
      integer*8 tp_ptr
      character(len=*),intent(in)::label
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
      integer TP_CURRENT_NODE_FORT
      external TP_CURRENT_NODE_FORT

      TP_CURRENT_NODE=TP_CURRENT_NODE_FORT(tp_ptr,trim(label)//NULL)

      return 
      end function TP_CURRENT_NODE

      integer function TP_CHANGE_NODE(tp_ptr,label)
      integer*8 tp_ptr
      character(len=*),intent(in)::label
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
      integer TP_CHANGE_NODE_FORT
      external TP_CHANGE_NODE_FORT
      TP_CHANGE_NODE=TP_CHANGE_NODE_FORT(tp_ptr,trim(label)//NULL)
      return 
      end function TP_CHANGE_NODE

      integer function TP_GET_NUMBER_OF_CNODES(tp_ptr,inode)
      integer*8 tp_ptr
      integer,intent(in) :: inode
      integer TP_GET_NUMBER_OF_CNODES_FORT
      external TP_GET_NUMBER_OF_CNODES_FORT

      TP_GET_NUMBER_OF_CNODES=TP_GET_NUMBER_OF_CNODES_FORT(tp_ptr,inode)
      return

      end function TP_GET_NUMBER_OF_CNODES

      integer function TP_GET_NUMBER_OF_CLEAVES(tp_ptr,ileaf)
      integer*8 tp_ptr
      integer,intent(OUT) :: ileaf
      integer TP_GET_NUMBER_OF_CLEAVES_FORT
      external TP_GET_NUMBER_OF_CLEAVES_FORT

      TP_GET_NUMBER_OF_CLEAVES=TP_GET_NUMBER_OF_CLEAVES_FORT(tp_ptr,ileaf)
      return

      end function TP_GET_NUMBER_OF_CLEAVES
      

      integer function TP_GET_ITH_NODE(tp_ptr,inode,node)
      integer*8 tp_ptr
      integer,intent(in) :: inode
      character(len=*),intent(OUT) :: node
      integer TP_GET_ITH_NODE_FORT
      external TP_GET_ITH_NODE_FORT
      integer iinode
      iinode=inode-1
!      write(6,*) 'TP_GET_ITH_NODE',iinode,inode,trim(node)
      TP_GET_ITH_NODE=TP_GET_ITH_NODE_FORT(tp_ptr,iinode,node)
!      write(6,*) 'TP_GET_ITH_NODE',iinode,inode,trim(node)
      return
      end function TP_GET_ITH_NODE


      integer function TP_GET_ITH_NODE_ORDER(tp_ptr,inode,node,order)
      integer*8 tp_ptr
      integer,intent(in) :: inode,order
      character(len=*),intent(OUT) :: node
      integer TP_GET_ITH_NODE_FORT
      external TP_GET_ITH_NODE_FORT
      integer iinode
      iinode=inode-1
!      write(6,*) 'TP_GET_ITH_NODE',iinode,inode,trim(node)
      TP_GET_ITH_NODE=TP_GET_ITH_NODE_ORDER_FORT(tp_ptr,iinode,node,order)
!      write(6,*) 'TP_GET_ITH_NODE',iinode,inode,trim(node)
      return
      end function TP_GET_ITH_NODE_ORDER


      integer function TP_GET_ITH_LEAF(tp_ptr,ileaf,leaf)
      integer*8 tp_ptr
      integer,intent(in) :: ileaf
      character(len=*),intent(OUT) :: leaf
      integer TP_GET_ITH_LEAF_FORT
      external TP_GET_ITH_LEAF_FORT
      integer iileaf
      iileaf=ileaf-1
      TP_GET_ITH_LEAF=TP_GET_ITH_LEAF_FORT(tp_ptr,iileaf,leaf)
      return
      end function TP_GET_ITH_LEAF

      integer function TP_GET_ITH_LEAF_ORDER(tp_ptr,ileaf,leaf,order)
      integer*8 tp_ptr
      integer,intent(in) :: ileaf,order
      character(len=*),intent(OUT) :: leaf
      integer TP_GET_ITH_LEAF_FORT
      external TP_GET_ITH_LEAF_FORT
      integer iileaf
      iileaf=ileaf-1
      TP_GET_ITH_LEAF=TP_GET_ITH_LEAF_ORDER_FORT(tp_ptr,iileaf,leaf,order)
      return
      end function TP_GET_ITH_LEAF_ORDER

      integer function TP_CONVERT_INT1(tp_ptr,value,ierror)
      integer*8 tp_ptr
      integer*1 TP_CONVERT_CHAR
      character(len=*),intent(in)::value
      integer ierror
      TP_CONVERT_INT1=TP_CONVERT_CHAR(tp_ptr,value,ierror)
      return 
      end function TP_CONVERT_INT1

      integer function TP_CONVERT_INT2(tp_ptr,value,ierror)
      integer*8 tp_ptr
      integer*2 TP_CONVERT_SHORT
      character(len=*),intent(in)::value
      integer ierror
      TP_CONVERT_INT2=TP_CONVERT_SHORT(tp_ptr,value,ierror)
      return 
      end function TP_CONVERT_INT2

      integer function TP_CONVERT_INT4(tp_ptr,value,ierror)
      integer*8 tp_ptr
      integer TP_CONVERT_INT
      character(len=*),intent(in)::value
      integer ierror
      TP_CONVERT_INT4=TP_CONVERT_INT(tp_ptr,value,ierror)
      return 
      end function TP_CONVERT_INT4

      integer function TP_CONVERT_INT8(tp_ptr,value,ierror)
      integer*8 tp_ptr
      integer*8 TP_CONVERT_LONG_LONG
      character(len=*),intent(in)::value
      integer ierror
      TP_CONVERT_INT8=TP_CONVERT_LONG_LONG(tp_ptr,value,ierror)
      return 
      end function TP_CONVERT_INT8


      integer function TP_GET_INSTANCE_SINGLETON(tp_ptr)
      integer TP_GET_INSTANCE_SINGLETON_FORT
      external TP_GET_INSTANCE_SINGLETON_FORT
      integer*8 tp_ptr
      TP_GET_INSTANCE_SINGLETON=TP_GET_INSTANCE_SINGLETON_FORT(tp_ptr)
      return
      end

      integer function TP_CREATE_INSTANCE(tp_ptr)
      integer TP_CREATE_INSTANCE_FORT
      external TP_CREATE_INSTANCE_FORT
      integer*8 tp_ptr
      TP_CREATE_INSTANCE=TP_CREATE_INSTANCE_FORT(tp_ptr)
      return
      end

      integer function TP_DELETE_INSTANCE(tp_ptr)
      integer TP_DELETE_INSTANCE_FORT
      external TP_DELETE_INSTANCE_FORT
      integer*8 tp_ptr

      TP_DELETE_INSTANCE=TP_DELETE_INSTANCE_FORT(tp_ptr)
      return
      end


      integer function TP_UPDATE_VALUE(tp_ptr,label,value)
      integer TP_UPDATE_VALUE_FORT
      external TP_UPDATE_VALUE_FORT
      integer*8 tp_ptr
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
      character(len=*),intent(in)::label
      character(len=*),intent(in)::value

      TP_UPDATE_VALUE=TP_UPDATE_VALUE_FORT(tp_ptr,trim(label)//NULL,trim(value)//NULL)

      return
      end

      integer function TP_CREATE_LEAF(tp_ptr,label,value)
      integer TP_CREATE_LEAF_FORT
      external TP_CREATE_LEAF_FORT
      integer*8 tp_ptr

      character(len=*),intent(in)::label
      character(len=*),intent(in)::value
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)

      TP_CREATE_LEAF=TP_CREATE_LEAF_FORT(tp_ptr,trim(label)//NULL,trim(value)//NULL)

      return
      end

      integer function TP_DELETE_LEAF(tp_ptr,label)
      integer TP_DELETE_LEAF_FORT
      external TP_DELETE_LEAF_FORT
      integer*8 tp_ptr
      character(len=*),intent(in)::label
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)

      TP_DELETE_LEAF=TP_DELETE_LEAF_FORT(tp_ptr,trim(label)//NULL)

      return
      end

      integer function TP_SPLIT_RANGE(tp_ptr,label,from,to,step)
      integer TP_SPLIT_RANGE_FORT
      external TP_SPLIT_RANGE_FORT
      integer*8 tp_ptr
      character(len=*),intent(in)::label
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
      real*8 from,to,step

      TP_SPLIT_RANGE=TP_SPLIT_RANGE_FORT(tp_ptr,trim(label)//NULL,from,to,step)

      return
      end

      integer function TP_EXPAND_RANGE(tp_ptr,label,expanded)
      integer TP_EXPAND_RANGE_FORT
      external TP_EXPAND_RANGE_FORT
      integer*8 tp_ptr
      character(len=*),intent(in)::label
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
      real*8 expanded(128)

      TP_EXPAND_RANGE=TP_EXPAND_RANGE_FORT(tp_ptr,trim(label)//NULL,expanded)

      return
      end

      integer function TP_SPLIT_LIST(tp_ptr,label,list,order)
      integer TP_SPLIT_LIST_FORT
      external TP_SPLIT_LIST_FORT
      integer*8 tp_ptr
      character(len=*),intent(in)::label
      CHARACTER(LEN=1), PARAMETER :: NULL = CHAR(0)
      real*8 list(128)

      TP_SPLIT_LIST=TP_SPLIT_LIST_FORT(tp_ptr,trim(label)//NULL,list,order)

      return
      end


