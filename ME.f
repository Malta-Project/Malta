      FUNCTION me(S, T, U, T14, T24, S34, MT, GS, Nc)
      REAL*8 S, T, U, T14, T24, S34, MT, GS, Nc
      REAL*8 dummy, Denom, me
      REAL*8 w(105)

      w(1)=S**(-1)
      w(2)=S34**(-1)
      w(3)=1/( - U - T24 - S + 2*MT**2)
      w(4)=Nc**(-1)
      w(5)=1/(U + T24 + S34 - 2*MT**2)
      w(6)=1/( - U - T - S34 + 2*MT**2)
      w(7)=1/( - T24 - T14 - S34 + 2*MT**2)
      w(8)=Nc**2
      w(9)=w(8) - 3
      w(9)=w(9)*Nc
      w(9)=w(9) + 2*w(4)
      w(10)=GS**6
      w(11)=w(9)*w(10)
      w(12)=w(1)*w(11)
      w(13)=w(10)*w(2)
      w(14)=w(9)*w(13)
      w(15)=w(12) - w(14)
      w(16)=MT**2
      w(17)=w(16)*w(10)
      w(18)=w(1)*w(2)
      w(19)=w(17)*w(9)*w(18)
      w(20)=6*w(19)
      w(21)=w(15) + w(20)
      w(21)=w(21)*w(16)
      w(21)=w(21) - 3*w(11)
      w(22)=2*w(16)
      w(21)=w(21)*w(22)
      w(12)=w(12) + 5*w(19)
      w(12)=w(12)*w(22)
      w(23)=w(19)*U
      w(24)=w(23) + w(11)
      w(25)= - w(12) + w(24)
      w(25)=U*w(25)
      w(26)=w(18)*w(11)
      w(27)=w(26)*U
      w(20)=w(20) - w(27)
      w(20)=w(20)*U
      w(28)=w(27) - w(19)
      w(28)=w(28)*T14
      w(20)=w(11) + w(20) - w(28)
      w(28)=3*w(19)
      w(29)=w(28) + w(14)
      w(29)=w(29)*w(22)
      w(30)= - w(29) + w(20)
      w(30)=T14*w(30)
      w(31)=MT**4
      w(32)=w(31)*w(26)
      w(23)= - w(23) + 2*w(32)
      w(32)=2*U
      w(33)=w(26)*w(32)
      w(34)=w(33) - w(28)
      w(34)=w(34)*T14
      w(23)=w(34) + 3*w(23)
      w(34)= - T24*w(23)
      w(25)=w(34) + w(30) + w(21) + w(25)
      w(25)=w(7)*w(25)
      w(30)=w(4) - Nc
      w(34)=w(30)*w(17)*w(18)
      w(35)=w(30)*w(10)
      w(36)=w(35)*w(1)
      w(37)=w(36) + 5*w(34)
      w(37)=w(37)*w(22)
      w(38)=3*w(34)
      w(39)=w(38)*U
      w(39)=w(39) + w(35)
      w(40)=w(34)*T24
      w(41)=w(35)*U
      w(42)=w(41)*w(18)
      w(43)=w(42) - w(38)
      w(44)=2*w(36)
      w(45)= - w(44) + w(43)
      w(45)=T14*w(45)
      w(45)= - w(40) + w(45) + w(37) - w(39)
      w(45)=T24*w(45)
      w(46)=w(35)*w(2)
      w(47)=w(46) - w(36)
      w(48)= - w(47) + 6*w(34)
      w(48)=w(48)*w(16)
      w(48)=w(48) - 3*w(35)
      w(48)=w(48)*w(16)
      w(47)=w(47) - w(38)
      w(47)=w(47)*w(16)
      w(47)=w(47) + w(35)
      w(49)=w(32)*w(34)
      w(50)= - w(49) - w(47)
      w(50)=T14*w(50)
      w(51)=3*w(31)
      w(52)=w(42)*w(51)
      w(50)=w(50) - w(48) + w(52)
      w(45)=2*w(50) + w(45)
      w(50)=2*w(6)
      w(45)=w(45)*w(50)
      w(52)=w(2)**2
      w(53)=w(52)*w(10)
      w(54)=w(8) - 1
      w(54)=w(54)*Nc
      w(55)=w(54)*w(53)
      w(56)=3*w(55)
      w(57)=w(17)*w(52)
      w(58)=w(1)*w(54)
      w(59)=w(58)*w(57)
      w(60)=10*w(59)
      w(61)=w(10)*w(54)
      w(62)=w(61)*w(18)
      w(63)=2*w(62)
      w(64)=w(63) + w(56) + w(60)
      w(64)=w(64)*w(16)
      w(65)=w(61)*w(2)
      w(66)=3*w(65)
      w(64)=w(64) - w(66)
      w(67)=w(55) + 7*w(59)
      w(68)=U*w(67)
      w(69)=w(58)*w(53)
      w(70)=w(69)*U
      w(71)=w(59) - w(70)
      w(71)=T14*w(71)
      w(68)=w(71) + w(68) - w(64)
      w(68)=T14*w(68)
      w(71)=w(57)*w(30)
      w(72)=2*w(71)
      w(73)=w(72) + w(46)
      w(74)= - T24 - U
      w(74)=w(73)*w(74)
      w(75)=w(46) + 3*w(71)
      w(76)=4*w(16)
      w(75)=w(75)*w(76)
      w(77)=w(41)*w(52)
      w(78)= - 2*w(77) - w(73)
      w(78)=T14*w(78)
      w(79)=S*w(71)
      w(74)= - 4*w(79) + w(78) + w(75) + w(74)
      w(74)=S*w(74)
      w(75)=w(77) - w(72)
      w(78)= - U*w(75)
      w(79)=w(71) - w(77)
      w(79)=T14*w(79)
      w(78)=w(78) + w(79)
      w(78)=T14*w(78)
      w(75)=w(75)*T14
      w(79)=T24 - w(32)
      w(79)=w(71)*w(79)
      w(79)=w(75) + w(79)
      w(79)=T24*w(79)
      w(80)=U**2*w(71)
      w(74)=w(74) + w(79) + w(80) + w(78)
      w(74)=w(5)*w(74)
      w(8)=w(8) - 2
      w(8)=w(8)*Nc
      w(8)=w(8) + w(4)
      w(78)=w(8)*w(57)
      w(79)=4*w(78)
      w(13)=w(8)*w(13)
      w(80)=w(79) - w(13)
      w(81)=3*w(16)
      w(82)=w(81)*w(80)
      w(53)=w(8)*w(53)
      w(83)=w(53)*T14
      w(84)=w(83) + w(13)
      w(85)=6*w(78)
      w(86)= - w(85) + w(84)
      w(86)=T14*w(86)
      w(87)= - w(13) + 2*w(78)
      w(88)=w(83) - w(87)
      w(88)=T24*w(88)
      w(86)=w(88) + w(82) + w(86)
      w(86)=T14*w(86)
      w(81)=w(87)*w(81)
      w(88)=5*w(78)
      w(89)= - w(88) + w(84)
      w(89)=T14*w(89)
      w(81)=w(81) + w(89)
      w(81)=S*w(81)
      w(80)=w(80)*w(22)
      w(89)=w(8)*w(10)
      w(80)=w(80) - w(89)
      w(80)=w(80)*w(16)
      w(81)=w(81) - w(80) + w(86)
      w(81)=w(3)*w(81)
      w(86)=w(63) + w(55)
      w(90)=w(86) + 12*w(59)
      w(90)=w(90)*w(16)
      w(90)=w(90) - w(65)
      w(91)=w(63) + 5*w(59)
      w(92)= - w(32)*w(69)
      w(92)=w(92) + w(91)
      w(92)=T14*w(92)
      w(93)=4*U
      w(94)=w(59)*w(93)
      w(92)=w(92) + w(94) - w(90)
      w(92)=T24*w(92)
      w(60)=w(86) + w(60)
      w(60)=w(60)*w(16)
      w(60)=w(60) - 7*w(65)
      w(60)=w(60)*w(22)
      w(86)= - U*w(90)
      w(25)=w(81) + w(74) + w(45) + w(25) + w(92) + w(68) + w(60) +
     & w(86)
      w(25)=w(3)*w(25)
      w(15)=w(15) + w(28)
      w(15)=w(15)*w(16)
      w(11)=w(15) - w(11)
      w(11)=2*w(11)
      w(15)=w(26)*T14
      w(15)= - w(27) - w(15) + 4*w(19)
      w(15)=w(15)*T24
      w(26)=2*w(10)
      w(9)=w(26)*w(9)*w(1)
      w(9)=w(9) + w(28)
      w(27)=U*w(9)
      w(14)= - w(19) + 2*w(14)
      w(19)=w(33) + w(14)
      w(19)=T14*w(19)
      w(19)=w(15) + w(19) - w(11) + w(27)
      w(19)=w(7)*w(19)
      w(27)=w(38) + w(46)
      w(27)=w(27)*w(22)
      w(28)= - w(34) + 2*w(46)
      w(45)=w(42) - w(28)
      w(45)=T14*w(45)
      w(18)=w(35)*w(18)
      w(46)=w(18)*T14
      w(68)= - w(46) + w(43)
      w(74)=w(18)*T24
      w(68)=2*w(68) + w(74)
      w(68)=T24*w(68)
      w(39)=w(68) + w(45) + w(27) - w(39)
      w(39)=w(39)*w(50)
      w(45)=w(79) + 3*w(13)
      w(45)=w(45)*w(16)
      w(45)=w(45) - w(89)
      w(68)=w(13) + w(78)
      w(79)=2*T14
      w(81)= - w(68)*w(79)
      w(86)=T24*w(87)
      w(83)= - 3*w(78) + w(83)
      w(83)=S*w(83)
      w(81)=w(83) + w(86) + w(81) + w(45)
      w(81)=w(3)*w(81)
      w(52)=w(35)*w(52)
      w(83)=T24*w(52)
      w(52)=T14*w(52)
      w(52)= - w(83) + w(52) + w(72) + w(77)
      w(52)=T24*w(52)
      w(72)= - 2*w(83) - w(73)
      w(72)=S*w(72)
      w(73)= - w(71)*w(32)
      w(52)=w(72) + w(52) + w(73) + w(75)
      w(52)=w(5)*w(52)
      w(72)=w(91)*U
      w(73)= - w(59) + 2*w(55)
      w(75)=2*w(73) + w(70)
      w(75)=T14*w(75)
      w(77)=T14 - w(32)
      w(77)=w(69)*w(77)
      w(77)=w(67) + w(77)
      w(77)=T24*w(77)
      w(19)=w(81) + w(52) + w(39) + w(19) + w(77) + w(75) + w(72) -
     & w(64)
      w(19)=w(3)*w(19)
      w(39)=w(46) - w(38) - w(42)
      w(39)=2*w(39) + w(74)
      w(39)=T24*w(39)
      w(42)=w(43)*T14
      w(42)=w(42) - w(35)
      w(38)= - w(44) - w(38)
      w(38)=U*w(38)
      w(37)=w(39) + w(38) + w(37) + w(42)
      w(38)=2*w(7)
      w(37)=w(37)*w(38)
      w(39)=w(69)*T24
      w(43)=w(79)*w(69)
      w(44)= - w(39) - w(43) + w(70) + w(67)
      w(44)=T24*w(44)
      w(15)=w(15) - w(23)
      w(15)=w(6)*w(15)
      w(23)=2*w(59) - w(70)
      w(23)=w(23)*w(79)
      w(15)=w(15) + w(37) + w(44) + w(23) + w(72) - w(90)
      w(15)=w(5)*w(15)
      w(23)=w(89)*w(1)
      w(37)=w(1)**2
      w(44)=w(17)*w(37)
      w(46)=w(8)*w(44)
      w(52)= - 5*w(23) + 8*w(46)
      w(52)=w(52)*w(16)
      w(52)=w(52) + w(89)
      w(69)= - w(23) + 3*w(46)
      w(72)=w(69)*w(32)
      w(75)=w(37)*w(89)
      w(77)=w(75)*U
      w(81)= - w(46) + w(77)
      w(81)=S34*w(81)
      w(86)=2*w(46)
      w(92)=w(86) - w(23)
      w(94)=T24*w(92)
      w(72)=w(94) + w(81) + w(72) - w(52)
      w(72)=w(7)*w(72)
      w(81)=w(54)*w(44)
      w(94)=w(2)*w(81)
      w(95)=2*w(94)
      w(96)=w(61)*w(37)
      w(97)=w(95) - w(96)
      w(97)=3*w(97)
      w(98)=w(65)*w(37)
      w(99)=w(98)*U
      w(100)=4*w(99)
      w(101)=w(98)*T24
      w(102)=2*w(101) - w(97) + w(100)
      w(102)=T24*w(102)
      w(10)=w(58)*w(10)
      w(103)=5*w(10)
      w(104)= - w(103) + 9*w(65)
      w(104)=w(104)*w(1)
      w(104)=w(104) - w(95)
      w(104)=w(104)*w(16)
      w(105)=2*w(65)
      w(104)=w(104) - w(105)
      w(26)=w(58)*w(26)
      w(26)=w(26) - w(66)
      w(26)=w(26)*w(1)
      w(26)=w(26) + w(95)
      w(58)=U*w(26)
      w(58)=w(72) + w(102) + w(58) + w(104)
      w(58)=w(7)*w(58)
      w(34)=w(74) - w(34)
      w(50)=w(34)*w(50)
      w(66)=w(71) - w(83)
      w(66)=w(5)*w(66)
      w(71)=w(53)*T24
      w(72)=w(71) + w(84)
      w(74)= - w(3)*w(72)
      w(39)=w(74) + w(66) + w(50) + w(59) - w(39)
      w(39)=w(3)*w(39)
      w(50)=w(92) - w(77)
      w(66)= - T24*w(75)
      w(66)=w(66) + w(50)
      w(66)=w(7)*w(66)
      w(66)=w(66) + w(101) - w(63) - w(99)
      w(66)=w(7)*w(66)
      w(34)=w(5)*w(34)*w(38)
      w(34)=w(39) + w(66) + w(34)
      w(34)=T*w(34)
      w(15)=w(34) + w(19) + w(58) + w(15)
      w(15)=T*w(15)
      w(19)=3*w(36)
      w(30)=w(44)*w(30)
      w(34)= - w(19) + 16*w(30)
      w(39)=w(35)*w(37)
      w(44)=w(39)*w(79)
      w(39)=w(39)*S34
      w(41)=w(41)*w(37)
      w(58)= - w(44) - w(39) - 4*w(41) + w(34)
      w(58)=T14*w(58)
      w(66)=4*w(30)
      w(74)=w(39) + w(66) - w(41)
      w(74)=S34*w(74)
      w(83)=8*w(30)
      w(84)=2*w(41)
      w(102)= - w(36) + w(83) - w(84)
      w(39)= - w(44) + w(39) + w(102)
      w(39)=T24*w(39)
      w(19)=w(19) - w(83)
      w(19)=w(19)*w(76)
      w(34)= - w(84) + w(34)
      w(34)=U*w(34)
      w(19)=w(39) + w(58) + w(74) + w(34) - w(35) + w(19)
      w(19)=T24*w(19)
      w(34)=U*w(102)
      w(39)=w(66) - w(36)
      w(44)= - w(39)*w(76)
      w(58)=w(66) - 3*w(41)
      w(58)=S34*w(58)
      w(74)=2*w(30)
      w(41)=w(74) - w(41)
      w(41)=w(41)*w(79)
      w(34)=w(41) + w(58) + w(44) + w(34)
      w(34)=T14*w(34)
      w(41)=w(36) - w(74)
      w(41)=w(41)*w(76)
      w(44)=w(36) - w(30)
      w(44)=S34*w(44)
      w(58)=U*w(66)
      w(41)=w(44) + w(58) + w(35) + w(41)
      w(41)=S34*w(41)
      w(36)= - 5*w(36) + 6*w(30)
      w(36)=w(36)*w(76)
      w(35)=w(35) + w(36)
      w(35)=w(35)*w(16)
      w(36)= - w(39)*w(16)
      w(30)=U*w(30)
      w(30)=w(36) + w(30)
      w(30)=w(30)*w(93)
      w(19)=w(19) + w(34) + w(41) + w(35) + w(30)
      w(19)=w(7)*w(19)
      w(30)= - T14*w(98)
      w(26)=w(30) + w(100) + w(26)
      w(26)=T14*w(26)
      w(30)= - w(62) + 10*w(94)
      w(34)=3*w(99)
      w(35)=w(101) + w(34) - w(30)
      w(35)=T24*w(35)
      w(36)=7*w(10) + 5*w(65)
      w(36)=w(36)*w(1)
      w(36)=w(36) - 22*w(94)
      w(36)=w(36)*w(16)
      w(36)=w(36) - w(10)
      w(39)=w(10) + 4*w(65)
      w(39)=w(39)*w(1)
      w(39)=w(39) - 18*w(94)
      w(41)=w(32)*w(98)
      w(44)=w(41) + w(39)
      w(44)=U*w(44)
      w(58)= - S34*w(96)
      w(26)=w(35) + w(26) + w(58) + w(44) - w(36)
      w(26)=T24*w(26)
      w(35)= - 4*w(46) + w(77) + w(23)
      w(44)=T24 + S34
      w(44)=w(75)*w(44)
      w(44)=w(44) + w(35)
      w(44)=T24*w(44)
      w(58)=w(92)*U
      w(66)= - S34*w(69)
      w(74)= - T14 + S34
      w(74)=w(75)*w(74)
      w(74)=2*w(69) + w(74)
      w(74)=T14*w(74)
      w(8)=w(17)*w(8)*w(1)
      w(17)=w(44) + w(74) + w(66) - w(8) - w(58)
      w(17)=T24*w(17)
      w(44)=T14*w(50)
      w(46)= - S34*w(46)
      w(44)=w(44) + w(46) + w(58) - w(52)
      w(44)=T14*w(44)
      w(23)= - w(86) + 3*w(23)
      w(23)=w(23)*w(22)
      w(23)=w(23) + w(89)
      w(46)=S34*w(92)
      w(46)= - w(23) + w(46)
      w(46)=w(16)*w(46)
      w(17)=w(17) + w(44) + w(46)
      w(17)=w(6)*w(17)
      w(41)= - w(97) + w(41)
      w(41)=U*w(41)
      w(44)= - w(63) + w(99)
      w(44)=T14*w(44)
      w(41)=w(44) + w(41) + w(104)
      w(41)=T14*w(41)
      w(44)= - 5*w(96) + 6*w(94)
      w(44)=w(44)*w(22)
      w(44)=w(44) + w(103)
      w(44)=w(44)*w(16)
      w(44)=w(44) + w(61)
      w(46)=w(10) + w(65)
      w(52)=w(46)*w(1)
      w(58)= - w(52) + 4*w(94)
      w(61)=w(58)*w(16)
      w(63)= - U*w(94)
      w(61)=w(61) + w(63)
      w(61)=w(61)*w(93)
      w(63)=w(81) - w(10)
      w(65)=S34*w(63)
      w(17)=w(17) + w(19) + w(26) + w(41) + w(65) + w(61) - w(44)
      w(17)=w(6)*w(17)
      w(14)=U*w(14)
      w(9)=w(33) + w(9)
      w(9)=T14*w(9)
      w(9)=w(9) - w(11) + w(14)
      w(9)=T24*w(9)
      w(11)= - w(29) + w(24)
      w(11)=U*w(11)
      w(12)= - w(12) + w(20)
      w(12)=T14*w(12)
      w(9)=w(9) + w(12) + w(21) + w(11)
      w(9)=w(6)*w(9)
      w(11)= - U*w(28)
      w(11)= - w(40) + w(11) + w(27) + w(42)
      w(11)=T24*w(11)
      w(12)= - U*w(47)
      w(14)=w(18)*w(51)
      w(14)=w(14) - w(49)
      w(14)=T14*w(14)
      w(12)=w(14) - w(48) + w(12)
      w(11)=2*w(12) + w(11)
      w(11)=w(11)*w(38)
      w(12)=w(53)*U
      w(14)= - 2*w(68) - w(12)
      w(14)=U*w(14)
      w(18)= - T14*w(87)
      w(19)= - w(85) + w(72)
      w(19)=T24*w(19)
      w(14)=w(19) + w(18) + w(82) + w(14)
      w(14)=T24*w(14)
      w(18)=w(71) + w(12) + w(13) - w(88)
      w(18)=T24*w(18)
      w(19)=w(87)*w(16)
      w(20)= - U*w(78)
      w(19)=w(19) + w(20)
      w(18)=3*w(19) + w(18)
      w(18)=S*w(18)
      w(12)= - w(12) + w(87)
      w(12)=T14*w(12)
      w(13)= - U*w(13)
      w(12)=w(12) + w(13) + w(45)
      w(12)=U*w(12)
      w(12)=w(18) + w(14) - w(80) + w(12)
      w(12)=w(5)*w(12)
      w(13)=w(73)*w(32)
      w(14)=w(70) + w(91)
      w(14)=T14*w(14)
      w(18)=T24*w(59)
      w(13)=w(18) + w(14) + w(13) - w(64)
      w(13)=T24*w(13)
      w(14)=U*w(59)
      w(14)=w(14) - w(64)
      w(14)=U*w(14)
      w(18)= - w(70) + w(67)
      w(18)=U*w(18)
      w(18)=w(18) - w(90)
      w(18)=T14*w(18)
      w(9)=w(12) + w(9) + w(11) + w(13) + w(18) + w(60) + w(14)
      w(9)=w(5)*w(9)
      w(11)= - w(56) + w(62)
      w(11)=T14*w(11)
      w(10)=w(11) - w(105) - w(10)
      w(10)=w(1)*w(10)
      w(11)=w(37)*w(54)*w(57)
      w(12)=8*w(11)
      w(13)=w(55) - 3*w(62)
      w(13)=w(1)*w(13)
      w(13)=w(13) - w(12)
      w(13)=U*w(13)
      w(14)=4*w(11)
      w(18)=w(55) + w(62)
      w(19)=w(18)*w(1)
      w(20)= - w(19) - w(14)
      w(20)=T24*w(20)
      w(21)=w(37)*w(31)
      w(21)=16*w(21) - 1
      w(21)=w(55)*w(21)
      w(10)=w(20) + w(13) + w(21) + w(10)
      w(10)=T24*w(10)
      w(13)= - w(55) + w(62)
      w(13)=w(1)*w(13)
      w(13)=w(13) + w(14)
      w(13)=w(13)*w(22)
      w(11)= - w(98) - 2*w(11)
      w(11)=U*w(11)
      w(11)=w(11) - w(52) + w(13)
      w(11)=w(11)*w(32)
      w(12)=w(19) - w(12)
      w(12)=w(12)*w(22)
      w(12)=w(12) + w(55) + 3*w(96)
      w(12)=w(12)*w(16)
      w(13)=4*w(59) - w(18)
      w(14)= - U*w(19)
      w(13)= - w(43) + 2*w(13) + w(14)
      w(13)=T14*w(13)
      w(10)=w(10) + w(13) + w(11) - 2*w(46) + w(12)
      w(11)=w(58)*w(76)
      w(12)=w(34) + w(39)
      w(12)=U*w(12)
      w(13)= - w(95) + w(99)
      w(13)=T24*w(13)
      w(11)=2*w(13) + w(11) + w(12)
      w(11)=T24*w(11)
      w(12)=U*w(35)
      w(13)= - T24*w(50)
      w(8)=w(13) - w(8) + w(12)
      w(8)=U*w(8)
      w(12)=w(92)*w(16)
      w(13)=w(77) - w(69)
      w(13)=U*w(13)
      w(12)=w(12) + w(13)
      w(12)=S34*w(12)
      w(13)= - w(23)*w(16)
      w(8)=w(12) + w(13) + w(8)
      w(8)=w(7)*w(8)
      w(12)=w(99) - w(30)
      w(12)=U*w(12)
      w(12)=w(12) - w(36)
      w(12)=U*w(12)
      w(13)= - U*w(96)
      w(13)=w(13) + w(63)
      w(13)=S34*w(13)
      w(8)=w(8) + w(11) + w(13) + w(12) - w(44)
      w(8)=w(7)*w(8)
      w(8)=w(15) + w(25) + w(9) + w(17) + 2*w(10) + w(8)

      me = 2*w(8)
      RETURN
      END
