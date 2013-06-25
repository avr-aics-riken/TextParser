!
! TextParser - Text Parsing Library
!
! Copyright (C) 2012-2013 Institute of Industrial Science, The University of Tokyo.
! All rights reserved.
!

program Example5
  implicit none

  include 'TextParser.inc'
  integer*8 tp_ptr
  integer status

  status = tp_create_instance(tp_ptr)
  status = tp_read(tp_ptr,'./tpp_examples/correct_label_4.txt')
  status = tp_update_value(tp_ptr,'/foo/qux/baz','10');
  status = tp_delete_leaf(tp_ptr,'/foo/qux/baz1');
  status = tp_change_node(tp_ptr,'/foo');
  status = tp_create_leaf(tp_ptr,'cdf','"filename"');
  status = tp_write(tp_ptr,'tmp_fort.tpp')
  status = tp_delete_instance(tp_ptr)

  end
