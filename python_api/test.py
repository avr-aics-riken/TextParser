#!/usr/bin/python2
# -*- coding: utf-8 -*-

###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
# Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
###################################################################################
#

import TextParser as tp
instance=tp.createInstance()

print "test for read()"
print tp.read(instance, "../Examples/test.tpp")

print "test for getVersionInfo()"
print tp.getVersionInfo()

print "test for getAllLabels()"
print tp.getAllLabels(instance)

print "test for getType()"
print tp.getType(instance, '/config/test_double_max')

print "test for getValue()"
print tp.getValue(instance, '/config/cell_start')

print "test for currentNode()"
print tp.currentNode(instance)

print "test for getNodes()"
print tp.getNodes(instance)

print "test for changeNode()"
print tp.changeNode(instance, 'config')

print "test for getLabels()"
print tp.getLabels(instance)

print "test for createLeaf()"
print tp.createLeaf(instance, 'foo', '"bar"')
print tp.getLabels(instance)  # fooという名前のleafノードが増えていることを確認

print "test for getValue()"
print tp.getValue(instance, '/config/foo')

print "test for updateValue()"
print tp.updateValue(instance, 'foo', 'hoge')
print tp.getValue(instance, '/config/foo') # fooの値がhogeに変わっていることを確認

print "test for deleteLeaf()"
print tp.deleteLeaf(instance, 'foo')
print tp.getLabels(instance) # fooという名前のリーフが無くなっていることを確認

print "test for splitRange()"
label=tp.getValue(instance, 'gridx31')[1]
print tp.splitRange(instance, label)

print "test for expandRange()"
label=tp.getValue(instance, 'gridx1')[1]
print tp.expandRange(instance,label)

print "test for splitList()"
label=tp.getValue(instance, 'gridx5')[1]
print tp.splitList(instance, label)


print "test for write()"
print tp.write(instance, 'tmp.output')

print "test for remove()"
print tp.remove(instance)
print tp.getAllLabels(instance)

print "test for deleteInstance()"
print tp.deleteInstance(instance)

print "test for getInstanceSingleton()"
instance=tp.getInstanceSingleton()
tp.read(instance, "../Examples/test.tpp")
print tp.getAllLabels(instance)
