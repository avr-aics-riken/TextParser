program Example7
  implicit none

  include 'TextParser.inc'
  integer*8 tp_ptr
  integer status
  character*512 label
  character*80 value
  integer i
  REAL*8  from,to,step
  REAL*8 expanded(6)
  REAL*8 list(4)
  REAL*8 check(6)
  REAL*8 check2(4)

  status = tp_create_instance(tp_ptr)
  status = tp_read(tp_ptr,'./tpp_examples/correct_range_list_1.tpp')
  status = tp_write(tp_ptr,'tmpf.tpp')

  status = tp_change_node(tp_ptr,'config')

  label='gridx3'

  value=''
  status = TP_GET_VALUE(tp_ptr,trim(label), value)

  if (status /= 0) then
     write(6,*) 'TP_GET_VALUE  status: ', status
  end if
  write(6,*) trim(value)
  status = TP_SPLIT_RANGE(tp_ptr,trim(value),from,to,step)
  write(6,*) "should be 50.,89.4,7 "
  write(6,*) from,' ',to,' ',step
          
  status = TP_EXPAND_RANGE(tp_ptr,trim(value),expanded)

  check(1)= 50.000000000000000     
  check(2)= 57.000000000000000     
  check(3) = 64.000000000000000     
  check(4)= 71.000000000000000     
  check(5)=  78.000000000000000     
  check(6)=  85.000000000000000     
  do i=1,6
  write(6,*) expanded(i),check(i)
  enddo

  value=''
  label='gridx5'
  status = TP_GET_VALUE(tp_ptr,trim(label), value)
  if (status /= 0) then
     write(6,*) 'TP_GET_VALUE  status: ', status
  end if
  write(6,*) trim(value)
  status = TP_SPLIT_LIST(tp_ptr,trim(value),list,0)
  check2(1)=-19.
  check2(2) = .4
  check2(3)= -3
  check2(4) = 10.3

  do i=1,4
     write(6,*) list(i),check2(i)
  enddo

  end
