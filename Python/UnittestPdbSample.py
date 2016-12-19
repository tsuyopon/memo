#!/usr/bin/env python
# -*- coding: utf-8 -*-
import unittest


class Sample(object):
	"""
	テスト対象のクラス
	"""
	def to_even(self, lst):
		"""
		リストを渡すと、偶数だけにして返す
		"""

		# 意図的にバグらせていて、奇数しか返さない
		evenlst = [v for v in lst if v % 2 == 1]
		return evenlst


class TestSample(unittest.TestCase):
	"""
	テストクラス
	"""

	def test_main(self):
		clazz = Sample()

		#  0 から 10 のリストを生成 [0, 1, 2, .....]
		lst = xrange(10)
		evenlst = clazz.to_even(lst)

		# 偶数かテストする
		for item in evenlst:
			num = item % 2
			self.assertEqual(0, num)


if __name__ == '__main__':
	unittest.main()
