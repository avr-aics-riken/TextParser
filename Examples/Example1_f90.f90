!
! TextParser - Text Parsing Library
!
! Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
! All rights reserved.
!
! Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
! All rights reserved.

! Copyright (c) 2016-2018 Research Institute for Information Technology, Kyushu University.
! All rights reserved.

! @file Example1_f90.f90
! @retval 0-success / 1-fail

program Example1

  implicit none

  integer read_write_parameters
  integer status
  status = 0

  status=status+ read_write_parameters("./tpp_examples/correct_basic_1.txt","./tpp_examples/correct_basic_1_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_2.txt","./tpp_examples/correct_basic_2_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_3.txt","./tpp_examples/correct_basic_3_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_4.txt","./tpp_examples/correct_basic_4_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_5.txt","./tpp_examples/correct_basic_5_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_6.txt","./tpp_examples/correct_basic_6_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_7.txt","./tpp_examples/correct_basic_7_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_8.txt","./tpp_examples/correct_basic_8_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_9.txt","./tpp_examples/correct_basic_9_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_10.txt","./tpp_examples/correct_basic_10_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_11.txt","./tpp_examples/correct_basic_11_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_12.txt","./tpp_examples/correct_basic_12_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_basic_13.txt","./tpp_examples/correct_basic_13_out.txt")

  status=status+ read_write_parameters("./tpp_examples/correct_string_1.txt","./tpp_examples/correct_string_1_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_string_2.txt","./tpp_examples/correct_string_2_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_string_3.txt","./tpp_examples/correct_string_3_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_string_4.txt","./tpp_examples/correct_string_4_out.txt")

  status=status+ read_write_parameters("./tpp_examples/correct_label_1.txt","./tpp_examples/correct_label_1_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_label_2.txt","./tpp_examples/correct_label_2_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_label_3.txt","./tpp_examples/correct_label_3_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_label_4.txt","./tpp_examples/correct_label_4_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_label_5.txt","./tpp_examples/correct_label_5_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_label_6.txt","./tpp_examples/correct_label_6_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_label_7.txt","./tpp_examples/correct_label_7_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_label_8.txt","./tpp_examples/correct_label_8_out.txt")

  status=status+ read_write_parameters("./tpp_examples/correct_cond_1.txt","./tpp_examples/correct_cond_1_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_2.txt","./tpp_examples/correct_cond_2_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_3.txt","./tpp_examples/correct_cond_3_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_4.txt","./tpp_examples/correct_cond_4_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_5.txt","./tpp_examples/correct_cond_5_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_6.txt","./tpp_examples/correct_cond_6_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_7.txt","./tpp_examples/correct_cond_7_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_8.txt","./tpp_examples/correct_cond_8_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_9.txt","./tpp_examples/correct_cond_9_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_10.txt","./tpp_examples/correct_cond_10_out.txt")

  status=status+ read_write_parameters("./tpp_examples/correct_cond_11.txt","./tpp_examples/correct_cond_11_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_12.txt","./tpp_examples/correct_cond_12_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_13.txt","./tpp_examples/correct_cond_13_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_14.txt","./tpp_examples/correct_cond_14_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_15.txt","./tpp_examples/correct_cond_15_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_16.txt","./tpp_examples/correct_cond_16_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_17.txt","./tpp_examples/correct_cond_17_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_18.txt","./tpp_examples/correct_cond_18_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_19.txt","./tpp_examples/correct_cond_19_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_cond_20.txt","./tpp_examples/correct_cond_20_out.txt")

  status=status+ read_write_parameters("./tpp_examples/correct_labelarray_1.txt","./tpp_examples/correct_labelarray_1_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_labelarray_2.txt","./tpp_examples/correct_labelarray_2_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_labelarray_3.txt","./tpp_examples/correct_labelarray_3_out.txt")
  status=status+ read_write_parameters("./tpp_examples/correct_labelarray_4.txt","./tpp_examples/correct_labelarray_4_out.txt")

  if (status.eq.0) then
    stop 0
  else
    stop 1
  end if

end program Example1


integer function read_write_parameters(ifilename, ofilename)
  character(*) ifilename, ofilename
  integer status
  include 'TextParser.inc'

  integer*8  tp_ptr ! for pointer to TextParser

  read_write_parameters = 0

  status = tp_create_instance(tp_ptr)
  read_write_parameters = read_write_parameters + status
  write(6,*) 'create instance : ', status

  write(6,*) 'input filename  : ', trim(ifilename)
  status = TP_READ(tp_ptr,ifilename)
  read_write_parameters = read_write_parameters + status
  write(6,*) 'Read status     : ', status

  status = TP_WRITE(tp_ptr,ofilename)
  read_write_parameters = read_write_parameters + status
  write(6,*) 'Write status    : ', status

  status = TP_REMOVE(tp_ptr)
  read_write_parameters = read_write_parameters + status
  write(6,*) 'Remove status   : ', status

  status = tp_delete_instance(tp_ptr)
  read_write_parameters = read_write_parameters + status
  write(6,*) 'Delete instance : ', status

end function
