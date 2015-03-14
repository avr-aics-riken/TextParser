!
! TextParser - Text Parsing Library
!
! Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
! All rights reserved.
!
! Copyright (c) 2014-2015 Advanced Institute for Computational Science, RIKEN.
! All rights reserved.

program Example4

      implicit none 

      integer move_and_get_parameters
      integer status
      include 'TextParser.inc'
      integer*8 tp_ptr

      status=tp_create_instance(tp_ptr)
!     status = move_and_get_parameters('Input0-1.txt',tp_ptr)
      status = move_and_get_parameters('./tpp_examples/correct_basic_1.txt',tp_ptr)
      status = tp_delete_instance(tp_ptr)
      
      status=tp_get_instance_singleton(tp_ptr)
!     status = move_and_get_parameters('Input4-1.txt',tp_ptr)
      status = move_and_get_parameters('./tpp_examples/correct_basic_12.txt',tp_ptr)
  
      end program Example4


!! move_and_get_parameters
!      integer function move_and_get_parameters(filename)
      recursive function move_and_get_parameters(filename,tp_ptr) RESULT(status)
      character(*) filename
      character*5 path
      integer status

      include 'TextParser.inc'
      integer*8 tp_ptr

      write(6,*) 'input filename: ', trim(filename)
      status = TP_READ(tp_ptr,filename)
	  if (status /= 0) then
          write(6,*) 'TP_READ   status: ', status
	  end if

      path = '/'
      call get_directory_parameters(filename, len_trim(path), trim(path),tp_ptr)

      status = TP_REMOVE(tp_ptr)  
      if (status /= 0) then
         write(6,*) 'TP_REMOVE status: ', status
      end if

      end function


!! get_directory_parameters
      recursive subroutine get_directory_parameters(filename, l_label, label,tp_ptr)
      character(*) filename, label
	  integer l_label
	  integer dir_number
	  integer parm_number
	  integer l_dir
	  character*512 dir_label
	  integer l_parm
	  character*512 parm_label
      character(80) value
	  integer l_value
	  integer value_type
      integer status

      include 'TextParser.inc'

      integer*8 tp_ptr

      write(6,*) filename,l_label,label


      status = TP_CHANGE_NODE(tp_ptr,label)
	  if (status /= 0) then
          write(6,*) 'TP_CHANGE_NODE  status: ', status
	  end if

      status = TP_CURRENT_NODE(tp_ptr,label)
	  if (status /= 0) then
          write(6,*) 'TP_CURRENT_NODE   status: ', status
	  end if
      write(6,*) 'Current directory: ', trim(label)

      status = TP_GET_NUMBER_OF_CNODES(tp_ptr,dir_number)
	  if (status /= 0) then
          write(6,*) 'TP_GET_NUMBER_OF_CNODES   status: ', status
	  end if
          write(6,*) 'Number of (daughter) Nodes in Current node.',dir_number
          if(dir_number.gt.0) then
             do i = 1, dir_number
                dir_label=''
                write(6,*) 'initialized ',trim(dir_label)
                status = TP_GET_ITH_NODE(tp_ptr,i, dir_label)
                write(6,*) 'initialized 2',trim(dir_label)
                if (status /= 0) then
                   write(6,*) 'TP_GET_ITH_NODE   status: ', status
                end if
                call get_directory_parameters(filename, len_trim(dir_label),trim(dir_label),tp_ptr)
             end do
	  endif

             status = TP_GET_NUMBER_OF_CLEAVES(tp_ptr,parm_number)
	  if (status /= 0) then
          write(6,*) 'TP_GET_NUMBER_OF_CLEAVES   status: ', status
	  end if
          write(6,*) 'Number of Leaves in Current node.',parm_number
          if(parm_number.gt.0) then
	   do i = 1, parm_number 
           parm_label=''
           value=''
           status = TP_GET_ITH_LEAF(tp_ptr,i, parm_label)
           if (status /= 0) then
              write(6,*) 'TP_GET_ITH_LEAF   status: ', status
	       end if
               write(6,*) i, ' ', trim(parm_label)
	 	  
          status = TP_GET_VALUE(tp_ptr,parm_label, value)
		  if (status /= 0) then
              write(6,*) 'TP_GET_VALUE   status: ', status
		  end if
          write(6,*) i ,' ', trim(value)

          status = TP_GET_TYPE(tp_ptr,parm_label, value_type)
		  if (status /= 0) then
              write(6,*) 'TP_GET_TYPE   status: ', status
		  end if
           write(6,*) i ,' type: ', value_type
	   end do
          endif
          status = TP_CURRENT_NODE(tp_ptr,label)
	  if (status /= 0) then
          write(6,*) 'TP_CURRENT_NODE   status: ', status
	  end if
	  if (trim(label) /= '/') then
          label = '..'
          status = TP_CHANGE_NODE(tp_ptr,label)
	      if (status /= 0) then
              write(6,*) 'TP_CHANGE_NODE   status: ', status
	      end if

          status = TP_Current_NODE(tp_ptr,label)
	      if (status /= 0) then
              write(6,*) 'TP_CURRENT_NODE   status: ', status
	      end if
          write(6,*) 'Current directory: ', trim(label)
	  end if
		  
      end subroutine get_directory_parameters
