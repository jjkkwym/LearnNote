1.Overview
蓝牙标准定义了5项安全服务：
• Authentication: verifying the identity of communicating devices based on their Bluetooth address. Bluetooth does not provide native user authentication.
• Confidentiality: preventing information compromise caused by eavesdropping by ensuring that only authorized devices can access and view transmitted data.
• Authorization: allowing the control of resources by ensuring that a device is authorized to use a service before permitting it to do so.
• Message Integrity: verifying that a message sent between two Bluetooth devices has not been altered in transit.SP.800-121r2
•Pairing/Bonding: creating one or more shared secret keys and the storing of these keys for use in subsequent connections in order to form a trusted device pair. 数据库

2.Pairing
配对是指“Master和Slave经过协商确立link key的过程。指的是下图中的第7部分。
蓝牙安全详解
Master和Slave有两种可选的配对方法：legacy pairing和Secure Connections。选择的依据是：当Master和Slave都支持Secure Connections（新方法）的时候，则使用Secure Connections。不然使用legacy pairing。编程

2.1.PIN/Legacy Pairing
2.1.1.overview
对于PIN/传统配对，当用户在一个或两个设备上输入彻底相同的机密的PIN码时，根据配置和设备类型，两个蓝牙设备同时得到连接密钥。下图从概念上描述了PIN码输入和密钥得到过程。注意，若是PIN码小于16字节，会用发起设备的地址（BD_ADDR）来补足PIN值以生成初始密钥。那些Ex框表明了蓝牙连接密钥得到过程所使用的加密算法。
蓝牙安全详解
完成连接密钥生成后，设备经过互相认证彼此来完成配对，以验证他们拥有相同的连接密钥。蓝牙配对中使用的PIN码能够是1到16个字节的二进制数或更常见的字母数字字符。对于低风险应用场景，典型的4位数PIN码多是足够的；对于要求更高安全级别的设备，应当使用更长的PIN码（例如， 8个字符的字母数字）。promise

2.1.2.Sequence Chars：
蓝牙安全详解

2.2.Secure Simple Pairing
2.2.1.overview
Secure Simple Pairing(SSP)经过提供一些关联模型来简化配对过程。这些模型具备适应不一样设备输入/输出能力的灵活性。SSP也经过增长ECDH公钥加密来改进安全性，以防止配对过程当中的被动窃听和中间人（MITM）***。
蓝牙安全详解安全

2.2.2.Sequence Chars
Simple Pairing配对过程如图所示，主要由下面四部分完成：
蓝牙安全详解session

2.2.2.1.Pairing Feature Exchange
用于交换双方有关鉴权的需求（authentication requirements），以及双方具备怎么的人机交互能力（IO capabilities）。其中最重要的是IO capabilities exchange。
蓝牙安全详解
IO的能力能够概括为以下的六种：架构

NoInputNoOutput
DisplayOnly
NoInputNoOutput1
DisplayYesNo
KeyboardOnly
KeyboardDisplay
上述的IO能力决定了后续的鉴权方式。
2.2.2.2.Public key exchange
两个设备之间交换Public key。 一旦设备收到对端设备的公钥，它就能够开始计算Diffie Hellman密钥（DHKey）。耗时较多，应该尽早开始，以便用户交互能够隐藏计算时间。 在步骤8以前不须要DHKey。
当 Public key的长度大于DM1包的长度时，要使用专门的PDU来进行数据发送。
蓝牙安全详解框架

2.2.2.3.Authentication
经过SMP协议进行实际的配对操做，根据阶段1 “Feature Exchange”的结果，有三种鉴权方法可选：ide

2.2.2.3.1.OOB鉴权：
若是双方都支持OOB鉴权，则选择该方式（优先级最高）。由配对的双方，在配对过程以外，额外的交互一些信息（譬如NFC），并以这些信息为输入，进行后续的配对操做。这些额外信息也称做OOB（out of band），OOB的交互过程称为OOB protocol。
蓝牙安全详解函数

2.2.2.3.2.MITM鉴权：
（man-in-the-middle）authentication，由二者方法：
Numeric Comparision方式鉴权：两个设备自行协商生成6个数字，并显示出来（要求两个设备具备显示能力），用户比较后进行确认（一致，或者不一致，要求设备有简单的yes or no的确认能力）。
蓝牙安全详解
Passkey Entry方式鉴权：经过输入配对码的方式鉴权。
蓝牙安全详解

2.2.2.3.3.Just Work:
Just Work，不须要用户参与，两个设备自行协商。

2.2.2.4.DHKey Checks
一旦设备完成鉴权过程，而且DHKey计算已完成，则检查生成的DHKey值。 若是成功，则两个设备都将完成向用户显示关于该过程的信息，不然控制器向主机发送消息以通知其中止显示该信息。
蓝牙安全详解

2.2.2.5.Calculate Link Key
当配对过程完成后，link key就能够从DHKey中计算获得，并用作后续交互过程的输入（KEY + 明文 => 加密数据），经过HCI_Link_Key_Notification来通知host。
蓝牙安全详解
通过上述配对过程后，双方已经产生了加密key，于是能够创建加密的链接。加密链接创建后，能够互相传送一些私密的信息，例如Encryption Information、Identity Information、Identity Address Information等。

3.Authentication
3.1.Legacy Authentication
蓝牙设备认证过程是质询-响应方案的形式。认证过程当中互动的每一个设备被称为申请者（Claimant）或验证者（Verifier）。申请者是试图证实本身身份的设备，而验证者是验证申请者身份的设备。质询-响应协议经过校验一个机密的密钥——蓝牙链路密钥来验证设备。下图从概念上展现了质询-响应验证方案。
蓝牙安全详解
认证过程当中的步骤以下图：
步骤 1. 验证者发送一个128位的随机质询（AU_RAND）给申请者
步骤 2. 申请者使用E1算法，以他或她的惟一的48位蓝牙设备地址、连接密钥和AU_RAND为输入，计算出一个认证响应。验证者执行一样的计算。只有E1输出的高32位才被用于认证的目的。128位输出中剩余的96位做为认证加密偏移（ACO）值，将被稍后用做输入以建立蓝牙加密密钥。
步骤 3. 申请者返回E1输出的高32位做为计算的响应——已签名的响应（SRES）——给验证者。
步骤 4. 验证者比较来自申请者的SRES和本身计算的值。
步骤 5. 若是两个32位值相等，认证被认为是成功的。若是两个32位值不相等，认证失败。
蓝牙安全详解
把这些步骤执行一遍就完成了一个单向认证。蓝牙标准容许执行单向和相互认证。用于相互认证时，验证者和申请者交换角色重复上述过程。
若是认证失败，蓝牙设备会等待必定时间间隔再作新的尝试。这个时间间隔呈指数级增加，以防止***者采用不一样的连接密钥以试错法来击破认证方案。重要的是，要注意该技术不提供针对离线***的安全保证。这种***利用窃听配对帧和穷尽猜想PIN码来肯定连接密钥。
注意，与认证相关的安全机制是彻底基于连接密钥的保密性。虽然蓝牙设备地址和随机质询值被视为公开参数，但链路密钥不是。链路密钥是在配对过程当中生成出来的，不该该在蓝牙设备以外暴露出来或经过无线链路传输。可是，链路密钥从主机到控制器（例如，PC到USB适配器）是明文传输，而当主机被用于密钥存储时状况相反。质询值是与认证过程相关的公开参数，对每次交互处理过程必须是随机且惟一的。质询值由蓝牙控制器中的伪随机数发生器生成。

3.2.Secure Authentication
若是双方都支持Secure Connection（BT4.1+）则 ，则使用Secure Authentication。
整个鉴权流程与legacy Authentication类似，不一样之处在于使用了H4,H5算法，而且会进行相互认证。当配对过程使用了P-256 Elliptic Curve ，则鉴权过程应该使用Secure Authentication。
蓝牙安全详解
Core sepc 中流程以下：
蓝牙安全详解

3.3.Key not exit
若是有鉴权需求，则发送鉴权请求：HCI_Link_Key_Request
蓝牙安全详解
若是host没有可用的key给Controller，则回复HCI_Link_Key_Request_Negative_Reply；
此时Controller发送CDM HCI_PIN_Code_Request_Reply,发起pair流程来生成一个可用的key；
蓝牙安全详解

4.Confidentiality
除了用于配对和认证的安全模式，蓝牙提供了独立的机密性服务来阻止试图窃听蓝牙设备之间交换的数据包的有效载荷。蓝牙有三种加密方式，可是只有其中两种提供实际的机密性。这些方式以下（加密方式2和3使用相同的加密机制）：

加密方式1——对任何流量不执行加密
加密方式2——单独寻址的流量使用基于单独链路密钥的加密密钥进行加密；广播流量未加密。
加密方式3——全部流量使用基于主机链路密钥的加密密钥进行加密。
4.1.E0 Encryption Algorithm
如图3-7，提供给加密算法的加密密钥是使用内部密钥发生器（KG）产生的。KG产生的流密码密钥是基于：128位连接密钥（它是一个被掌握于蓝牙设备内部的机密）、128位随机数（EN_RAND）和96位ACO值。ACO是在认证过程当中产生的(Legacy Authentication)，如图3-5所示。
蓝牙加密过程是基于流密码，E0。密钥流输出会和有效负载位进行异或操做，而后发送到接收设备。该密钥流是利用基于线性反馈移位寄存器（LFSRs）的加密算法产生的。加密函数采用如下参数做为输入：主设备地址（BD_ADDR）、128位随机数（EN_RAND），基于微微网时钟的时隙号和加密密钥。若是加密已启用，在每一个分组包传输以前，当这些参数被组合时，它们会初始化LFSRs。流密码中使用的时隙号随着每一个分组包改变；加密引擎会随每一个分组包被从新初始化，而其余变量保持不变。
蓝牙安全详解
加密密钥（KC）是从当前链路密钥算出的，而且其长度以单字节为增量在1字节到16字节间变化，其值是在主从设备间的协商过程当中被设置的。在本次协商期间，主设备给从设备一个建议的密钥大小。主设备建议的初始密钥大小是被制造商编程在控制器中的，且并不是老是16字节。在产品实现中，可设置一个“最小可接受的”密钥大小参数来防止恶意用户驱使密钥大小降到最小的1字节——这会使该链路的安全性变低。
重要的是，注意E0不是联邦信息处理标准（FIPS）批准的算法，且在算法强度方面没有受到详细审查。一项已公开的、理论上的已知明文***能够在2^38次计算中从新得到加密密钥，而暴力破解须要测试2^128个可能的密钥。若是通讯须要FIPS认证的加密保护（例如，为了保护联邦机构间传输的敏感信息），这种保护能够经过在原生蓝牙加密之上层叠FIPS承认的应用级加密。

4.2.AES-CCM Encryption Algorithm
如图3-8所示，提供给加密算法的加密密钥是使用h3函数生成的。 h3功能根据128位连接密钥产生流密码密钥，这是一个保存在蓝牙设备中的密钥;主设备的惟一48位蓝牙设备地址;从机的惟一48位蓝牙设备地址;一个固定密钥ID“btak”;和96位ACO值。 ACO在认证过程当中生成（Secure Authentication），如图3-6所示。经过获取原始加密密钥的128个最高有效位来缩短加密密钥。
蓝牙AES-CCM加密程序基于请求注释（RFC）3610，高级加密标准 - 具备密码块连接消息认证码的计数器。 AES-CCM加密功能将如下内容做为输入：加密密钥，加密随机数和有效负载位。 nonce格式有两种类型：用于ACL数据包的有效负载计数器格式和用于增eSCO的时钟格式（也包括11位日计数器） ）数据包。当启用AES-CCM加密时，ACL数据包包括一个4字节的消息完整性检查（MIC）。 eSCO数据包不包含MIC。
蓝牙安全详解

4.3.Sequence Chars：
4.3.1.Encryption requested
在配对或者鉴权完成后的任什么时候间点均可发起加密，经过发送CDM：HCI_Set_Connection_Encryption（master或slave都可）完成。
当slave发起时，将由slave发起LMP_encryption_mode_req，但后续的
LMP_encryption_key_size_req和LMP_start_encryption_req只能经过master发起。
蓝牙安全详解

4.3.2.Encryption off requested
蓝牙安全详解

4.3.3.Change Connection Link Key
master能够经过该流程Change Connection Link Key，当生成新的link key后，会再次向host通知。
蓝牙安全详解

4.3.4.Change Connection Link Key with Encryption Pause and Resume
与上面的流程不一样之处在于link key生成后会当即使用。先暂停加密过程，而后使用link key计算生成新的加密key，而后继续数据收发（使用新的加密key）。
蓝牙安全详解

4.3.5.Master Link Key
Master使用该流程，指定使用一个temporary link key（用于加密在piconet中广播消息）；或使用semi-permanent link（用于加密私有加密点对点通讯）。
CMD : HCI_Master_Link_Key 中的参数Key_Flag用于指明使用那种状况。
蓝牙安全详解
使用semi-permanent link（用于加密私有加密点对点通讯）：
蓝牙安全详解

5.Trust Levels, Service Security Levels, and Authorization
5.1.Security Mode
蓝牙BR/EDR/HS系列规范定义了四种安全模式。每一个蓝牙设备必须工做于这些模式之一。这些模式以安全模式1到4命名。这些模式决定了何时蓝牙设备开启安全性，而不是它是否支持安全功能。

安全模式1的设备被看做是无安全性的。安全功能（认证和加密）从未被开启，任由***者轻易地影响设备和链接。实际上，处于这个模式的蓝牙设备是“不加选择的”，没有采用任何机制来阻止其余开启蓝牙功能的设备与之创建链接。可是，若是一个远程设备启动了安全机制——好比配对、认证或加密请求——则一个安全模式1的设备须要参与进来。根据各个蓝牙规范版本，全部v2.0及更早的设备可以支持安全模式1，而v2.1及以后的设备可以使用安全模式1以向下兼容老的设备。可是NIST建议绝对不要使用安全模式1。
在安全模式2——服务级强制安全模式之中，安全过程可被启动于链路创建以后但逻辑信道创建以前。对于这种安全模式，一个本机的安全管理器（如在蓝牙架构中规定的）控制了对特定服务的访问。中心化的安全管理器维护着访问控制策略和与其余协议及设备使用者的接口。用于限制访问的不一样的安全策略和信任级别，能够针对并行运行的、具备不一样安全需求的应用来定义。这样一种状况是可能的，即在没有提供对一部分服务的权限的状况下，容许对其余服务的访问。在这种模式中，“受权”的概念——决定一个特定设备是否被容许访问一个特定服务的过程——被引入了。一般蓝牙服务发现能在任何安全要求（例如，认证、加密和/或受权）以前被执行。可是，全部其余的蓝牙服务应该须要全部的安全机制。
特别须要注意的是安全模式2中使用的认证和加密机制，它们是在控制器中实现的，这如同下面描述的安全模式3。全部v2.0及更早的设备可以支持安全模式2，可是v2.1及以后的设备仅为了向下兼容v2.0或更早的设备而支持它。
安全模式3是一种链路级强制安全模式。在这种模式中，一个蓝牙设备在彻底创建物理链路以前就会发起安全过程。运行在安全模式3之下的蓝牙设备对全部发出和收到的链接进行强制认证和加密。因此，在认证、加密和受权已经被执行前，甚至连服务发现也不能被执行。一旦一个设备已经被认证了，安全模式3的设备一般不会执行服务级的受权。可是，NIST建议应当执行服务级受权以阻止“认证滥用”——已被认证的远程设备在本地设备拥有者不知晓的状况下使用蓝牙服务。
全部v2.0及更早的设备可以支持安全模式3，但v2.1及以后的设备仅仅为了向下兼容的目的而可以支持它。
安全模式4相似于安全模式2，（在蓝牙2.1 + EDR中引入）是一种服务级别安全模式，其中安全程序在物理和逻辑链路创建以后启动。安全模式4使用安全简单配对（SSP），其中ECDH密钥协议用于链路密钥生成。在蓝牙4.0以前，P-192 Elliptic Curve被用于连接密钥生成，而且设备认证和加密算法与蓝牙2.0 + EDR和更早版本中的算法相同。蓝牙4.1引入了安全链接(Secure Connection)功能，容许使用P-256Elliptic Curve来生成链路密钥。在蓝牙4.1中，设备认证算法已升级为经FIPS批准的哈希消息认证码256位安全散列算法（HMAC-SHA-256）。加密算法已升级为经FIPS承认的具备CBC-MAC（AES-CCM）的AES计数器，该计数器还提供消息完整性。受安全模式4保护的服务的安全要求必须归类为如下之一：
• Level 4: Authenticated link key using Secure Connections required
• Level 3: Authenticated link key required
• Level 2: Unauthenticated link key required
• Level 1: No security required
• Level 0: No security required. (Only allowed for SDP)
是否验证链路密钥取决于所使用的SSP关联模型（参见第3.1.1.2节）。 当本地和远程设备都支持安全链接功能时，使用Secure Connections（安全链接）生成link key，这是NIST推荐的安全措施。 安全模式4须要加密全部服务（服务发现除外），而且对于2.1和更高版本的BR / EDR设备之间的通讯是强制性的。 可是，为了向后兼容，当与蓝牙2.0和不支持安全模式4的早期设备通讯时，安全模式4设备能够回退到其余三种安全模式中的任何一种。在这种状况下，NIST建议使用安全模式3。
蓝牙安全详解
蓝牙安全详解
除了四种安全模式，蓝牙容许不一样层次信任级别和服务安全级别。
两种蓝牙信任级别是信任和不信任。一个可信任的设备与其余设备有固定的关系，并拥有全部服务的彻底访问权限。不可信的设备与其余蓝牙设备没有已创建的关系，这致使不可信的设备受到对服务的限制访问。
可用的服务安全级别取决于使用的安全模式。安全模式1和3中，没有指定服务安全级别。安全模式2中，可强制执行如下安全性要求：
• Authentication required
• Encryption required
• Authorization required
所以，可用的服务安全级别包括上述的任何组合，包括无安全保护（一般只用于服务发现）。须要注意的是，BR/EDR加密不能在没有认证的状况下被执行，由于加密密钥是来源于认证过程的产出。
对于安全模式4，蓝牙规范为蓝牙服务规定了四个安全级别以便在SSP中使用。这些服务安全级别以下：
服务级别3——须要MITM保护和使用128bit加密。
服务级别3——须要MITM保护和加密；用户交互是可接受的。
服务级别2——只须要加密；MITM保护不是必要的。
服务级别1——不须要MITM保护和加密。最少的用户交互。
服务级别0——无MITM保护、加密或者用户交互。
蓝牙架构容许定义可设置信任关系的安全策略：即便可信的设备也只能获取对特定服务的访问权限。虽然蓝牙核心协议只能认证设备而不能认证用户，可是基于用户的认证仍然是可能的。蓝牙安全架构（经过安全管理器）容许应用实施更细致的安全策略。蓝牙特定的安全控制是在运行在链路层的，对应用层施加的安全控制来讲，该层是透明的。所以，蓝牙安全框架内经过应用层实现基于用户的认证和精细访问控制是可能的，虽然这样作已经超出了蓝牙规范的范围。
前面咱们介绍了Security Features of Bluetooth BR/EDR/HS，后续咱们进入LE Security Features介绍。
6.Security Features of Bluetooth Low Energy
蓝牙协议定义了一系列的复杂机制，用于处理和加密key有关的操做，这就是SM（Security Manager）。图示以下：
蓝牙安全详解
它的主要目的是为LE设备（LE only或者BR/EDR/LE）提供创建加密链接所需的key（STK or LTK）。为了达到这个目的，它定义了以下几类规范：
1）将生成加密key的过程称为Pairing（配对），并详细定义了Pairing的概念、操做步骤、实现细节等。
2）定义一个密码工具箱（Cryptographic Toolbox），其中包含了配对、加密等过程当中所需的各类加密算法。
3）定义一个协议（Security Manager Protocol，简称SMP），基于L2CAP链接，实现master和slave之间的配对、密码传输等操做。

6.1.LE Pairing
Pairing（配对）： 在SM的规范中，配对是指“Master和Slave经过协商确立用于加（解）密的key的过程”，主要由三个阶段组成：
蓝牙安全详解
展开以下：
蓝牙安全详解

阶段1，称做“Pairing Feature Exchange”，用于交换双方有关鉴权的需求（authentication requirements），以及双方具备怎么的人机交互能力（IO capabilities）。
阶段2，经过SMP协议进行实际的配对操做，根据阶段1 “Feature Exchange”的结果，有两种配对方法可选：LE legacy pairing和LE Secure Connections。
阶段3是可选的，通过阶段1和阶段2以后，双方已经产生了加密key，于是能够创建加密的链接。加密链接创建后，能够互相传送一些私密的信息，例如Encryption Information、Identity Information、Identity Address Information等。
Master和Slave有两种可选的配对方法：LE legacy pairing和LE Secure Connections选择的依据是：当Master和Slave都支持LE Secure Connections（新方法）的时候，则使用LE Secure Connections。不然，使用LE legacy pairing。
鉴权方式有三种：
OOB（out of band）
MITM（man-in-the-middle）authentication
Passkey Entry，经过输入配对码的方式鉴权
Numeric Comparison（只可用于LE Secure Connections）
Just Work
Just Work
注意：
虽然LE采用相似于BR/EDR SSP的配对方法(BT4.1+)名称，但LE配对不使用基于ECDH的加密且不提供无窃听的保护。所以，若是***者可以捕获LE配对帧，有可能肯定产生的LTK。
由于LE配对使用的是密钥传输而不是密钥协商，因此在LE配对期间须要一个密钥分配的步骤。如图3-9所示，LE配对始于两个设备商定临时密钥（TK），其值取决于所使用的配对方法。而后，这些设备之间交换随机数值，并将基于这些数值和TK来生成短时间密钥（STK）。随后，使用STK来给链路加密，这就允许安全的LTK、IRK和CSRK密钥分配。
6.1.1.LE Legacy Pairing
1）LE legacy pairing最终生成的是Short Term Key（双方共享），生成STK以后，用STK充当LTK，并将EDIV和Rand设置为0，去创建加密链接。
2）加密链接创建以后，双方能够自行生成Long Term Key（以及相应的EDIV和Rand），并经过后续的“Transport Specific Key Distribution”将它们共享给对方，以便后面从新创建加密链接所使用：
master和slave都要生成各自的LTK/EDIV/Rand组合，并共享给对方。由于加密链路的发起者须要知道对方的LTK/EDIV/Rand组合，而Master或者Slave都有可能从新发起链接。
3）STK的生成也比较简单，双方各提供一个随机数（MRand和SRand），并以TK为密码，执行S1加密算法便可。
4）TK是在鉴权的过程当中获得的，根据在阶段一选择的鉴权方法，TK能够是经过OOB获得，也能够是经过Passkey Entry获得，也能够是0（Just Work）。
注意：LE legacy pairing只能使用OOB、Passkey Entry或者Just Work三种鉴权方法（Numeric Comparison只有在LE Secure Connections时才会使用）。
蓝牙安全详解

6.1.2.LE Secure Simple Connections Pairing
LE Secure Connections pairing利用了椭圆曲线加密算法（P-256 elliptic curve），简单说明以下：
1）可使用OOB、Passkey Entry、Just Work以及Numeric Comparison四种鉴权方法。其中Numeric Comparison的流程和Just Work基本同样。
2）能够直接生成LTK（双方共享），而后直接使用LTK进行后续的链路加密，以及从新链接时的加密。
蓝牙安全详解

6.2.LE密钥生成和分配
一旦链路使用STK加密了，这两个设备就能够分配机密的密钥，如LTK、IRK和Connection Signature Resolving Key (CSRK)。
对于LE legacy pairing的LTK须要EDIV/Rand信息，由于LTK是各自生成的，不同，于是须要一个索引去查找某一个LTK（对比后面介绍的LE Secure Connections，LTK是直接在配对是生成的，于是就不须要这两个东西）。
在分配前，须要为密钥的生成肯定两个选项。设备能够简单地生成一些随机的128位值，并将它们存储在本地数据库（规范中称为“数据库查找”）。另外一个选项是使用单个128位的静态但随机的值来生成这些密钥；这个值被称为带有16位变化符（DIV）的加密根（ER），它对每一个受信设备是惟一的。这个选项在规范中被称为“密钥层次结构”。例如，这些密钥可使用下面的公式从ER、DIV和标识根（IR）得出：
LTK=d1（ER，DIV，0）
CSRK=d1（ER，DIV，1）
IRK=d1（IR，1，0）
函数d1被称为多元函数，该函数基于AES-128加密。然而，规范也容许其余密钥导出函数的使用。
使用密钥层次结构的方法，设备不须要为每一个受信设备存储多个128位密钥；相反，它仅须要存储其ER和每一个每一个设备惟一的DIV。从新链接期间，远程设备发送其EDIV（这是DIV的掩蔽版本）。而后，本地设备可根据ER和传送的EDIV来从新生成LTK和/或CSRK。若是数据加密或签名被成功设置，则验证了远程设备拥有正确的LTK或CRSK。若是不成功，则链路被丢弃。
注意，在上面的例子中，IRK是静态的和特定于设备的，所以能够先于配对过程生成。

6.3.LE encryption
LE Encryption要完成的事情：
数据发送方在须要发送数据的时候，按照必定的加密算法，将数据加密；
数据接收方在接收到数据的时候，按照等同的解密算法，将数据解密。
蓝牙安全详解
Master/Slave的LE Host会保存一个LTK（Long Term Key，至少128bits），对BLE用户（或者应用）来讲，这个Key是全部加密/解密动做源头；
每当为某个LE链接启动加密传输的时候，Master和Slave的LL会协商生成一个128bits的随机数SKD（Session Key Diversifier，128bits），并以它为输入，以LTK为key，经过Encryption Engine加密生成SessionKey；
每当有明文数据包须要发送的时候，须要对明文进行加密。加密的过程，是以明文数据包为输入，以SessionKey为Key，一样经过Encryption Engine加密生成密文数据包；
一样，每当收到密文数据包的时候，须要对密文解密。解密的过程，是以密文数据包为输入，以SessionKey为Key，一样经过Encryption Engine解密生成明文数据包。
对于上述过程，咱们考虑三个问题：
1）LTK是怎么来的？ ：由配对过程生成
2）SKD是个什么东西？怎么来的？ ：由下图交互生成
3）Encryption Engine又什么东西呢？ ：这个其实就是一个加密算法。
上面所提到的LTK和具体的加密过程相关，参考下面的sequence：
蓝牙安全详解
总结：
配对过程产生 ：LTK（Long Term Key） STK = s1(TK, Srand, Mrand),TK是实在鉴权的过程当中获得的。
开始加密协商出 ：SDK（Short Term Key）
controler A(SKDm) + controler B(SKDs) ==》 128b (SDK)
IVs + IVm ==》 IV(64b)
LTK + SDK + 加密引擎 ==》 sessionKey
sessionKey + 数据PDU + 加密引擎 ==》 加密数据