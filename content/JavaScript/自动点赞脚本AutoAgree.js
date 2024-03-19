//自动点赞脚本
function auto() {
    var isLike = document.getElementsByClassName("item qz_like_btn_v3 ")[0];
    if (isLike.attributes[6].value == 'like') {
        isLike.firstChild.click();
    }
    document.getElementsByClassName("ui-icon  icon-refresh-v9")[0].click();
}
var time = prompt("60") * 1000
setInterval(auto, time);
