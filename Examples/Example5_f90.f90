!
! TextParser - Text Parsing Library
!
! Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
! All rights reserved.
!
! Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
! All rights reserved.
!
! Copyright (c) 2016-2017 Research Institute for Information Technology, Kyushu University.
! All rights reserved.

! @file Example5_f90.f90
! @retval 0-success / 1-fail

program Example5
  implicit none

  include 'TextParser.inc'
  integer*8 tp_ptr
  integer status

  status = 0

  status = status + tp_create_instance(tp_ptr)
  status = status + tp_read(tp_ptr,'./tpp_examples/correct_label_4.txt')
  status = status + tp_update_value(tp_ptr,'/foo/qux/baz','10');
  status = status + tp_delete_leaf(tp_ptr,'/foo/qux/baz1');
  status = status + tp_change_node(tp_ptr,'/foo');
  status = status + tp_create_leaf(tp_ptr,'cdf','"filename"');
  status = status + tp_write(tp_ptr,'tmp_fort.tpp')
  status = status + tp_delete_instance(tp_ptr)

  if (status.eq.0) then
    stop 0
  else
    stop 1
  end if

end program Example5
