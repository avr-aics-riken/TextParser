!
! TextParser - Text Parsing Library
!
! Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
! All rights reserved.
!

program Example2

      implicit none 


      integer read_parameters
      integer status


    status= read_parameters("./tpp_examples/incorrect_basic_1.txt","./tpp_examples/incorrect_basic_1_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_2.txt","./tpp_examples/incorrect_basic_2_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_3.txt","./tpp_examples/incorrect_basic_3_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_4.txt","./tpp_examples/incorrect_basic_4_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_5.txt","./tpp_examples/incorrect_basic_5_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_6.txt","./tpp_examples/incorrect_basic_6_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_7.txt","./tpp_examples/incorrect_basic_7_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_8.txt","./tpp_examples/incorrect_basic_8_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_9.txt","./tpp_examples/incorrect_basic_9_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_10.txt","./tpp_examples/incorrect_basic_10_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_11.txt","./tpp_examples/incorrect_basic_11_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_12.txt","./tpp_examples/incorrect_basic_12_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_13.txt","./tpp_examples/incorrect_basic_13_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_14.txt","./tpp_examples/incorrect_basic_14_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_15.txt","./tpp_examples/incorrect_basic_15_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_16.txt","./tpp_examples/incorrect_basic_16_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_17.txt","./tpp_examples/incorrect_basic_17_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_18.txt","./tpp_examples/incorrect_basic_18_out.txt")
    status= read_parameters("./tpp_examples/incorrect_basic_19.txt","./tpp_examples/incorrect_basic_19_out.txt")
    status= read_parameters("./tpp_examples/incorrect_cond_1.txt","./tpp_examples/incorrect_cond_1_out.txt")
    status= read_parameters("./tpp_examples/incorrect_cond_2.txt","./tpp_examples/incorrect_cond_2_out.txt")
    status= read_parameters("./tpp_examples/incorrect_cond_3.txt","./tpp_examples/incorrect_cond_3_out.txt")
    status= read_parameters("./tpp_examples/incorrect_cond_4.txt","./tpp_examples/incorrect_cond_4_out.txt")
    status= read_parameters("./tpp_examples/incorrect_cond_5.txt","./tpp_examples/incorrect_cond_5_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_1.txt","./tpp_examples/incorrect_label_1_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_2.txt","./tpp_examples/incorrect_label_2_out.txt")
!    status= read_parameters("./tpp_examples/incorrect_label_3.txt","./tpp_examples/incorrect_label_3_out.txt")
!    status= read_parameters("./tpp_examples/incorrect_label_4.txt","./tpp_examples/incorrect_label_4_out.txt")
!    status= read_parameters("./tpp_examples/incorrect_label_5.txt","./tpp_examples/incorrect_label_5_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_6.txt","./tpp_examples/incorrect_label_6_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_7.txt","./tpp_examples/incorrect_label_7_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_8.txt","./tpp_examples/incorrect_label_8_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_9.txt","./tpp_examples/incorrect_label_9_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_10.txt","./tpp_examples/incorrect_label_10_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_11.txt","./tpp_examples/incorrect_label_11_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_12.txt","./tpp_examples/incorrect_label_12_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_13.txt","./tpp_examples/incorrect_label_13_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_14.txt","./tpp_examples/incorrect_label_14_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_15.txt","./tpp_examples/incorrect_label_15_out.txt")
    status= read_parameters("./tpp_examples/incorrect_label_16.txt","./tpp_examples/incorrect_label_16_out.txt")
!    status= read_parameters("./tpp_examples/incorrect_label_17.txt","./tpp_examples/incorrect_label_17_out.txt")
    status= read_parameters("./tpp_examples/incorrect_labelarray_1.txt","./tpp_examples/incorrect_labelarray_1_out.txt")
    status= read_parameters("./tpp_examples/incorrect_labelarray_2.txt","./tpp_examples/incorrect_labelarray_2_out.txt")
    status= read_parameters("./tpp_examples/incorrect_labelarray_3.txt","./tpp_examples/incorrect_labelarray_3_out.txt")

  
      end program Example2

      integer function read_parameters(ifilename, ofilename)
      character(*) ifilename, ofilename
      integer status
      include 'TextParser.inc'

      integer*8  tp_ptr ! for pointer to TextParser 

      status = tp_create_instance(tp_ptr);
      write(6,*) 'create instance: ', status

      write(6,*) 'input filename: ', trim(ifilename)
      status = TP_READ(tp_ptr,ifilename)
      write(6,*) 'Read   status: ', status

      status = TP_REMOVE(tp_ptr)  
      write(6,*) 'Remove status: ', status

      status = tp_delete_instance(tp_ptr);
      write(6,*) ' delete instance: ', status

      end function
