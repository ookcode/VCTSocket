/**
 * @module jsb_socketLogic
 */
var VCT = VCT || {};

/**
 * @class SocketLogic
 */
VCT.SocketLogic = {

/**
 * @method openWithIp
 * @param {char} arg0
 * @param {int} arg1
 */
openWithIp : function (
char, 
int 
)
{
},

/**
 * @method addListener
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @param {function} arg2
 */
addListener : function (
int, 
int, 
func 
)
{
},

/**
 * @method sendPackage
 * @param {VCT::Package} arg0
 */
sendPackage : function (
package 
)
{
},

/**
 * @method removeListener
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 */
removeListener : function (
int, 
int 
)
{
},

/**
 * @method close
 */
close : function (
)
{
},

/**
 * @method getInstance
 * @return {VCT::SocketLogic}
 */
getInstance : function (
)
{
    return VCT::SocketLogic;
},

};
