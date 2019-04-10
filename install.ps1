Write-Host "Make sure Python 3 is installed. This script installs psutil and feedparser using pip."
$confirmation = Read-Host -Prompt "Are you Sure You Want To Proceed (y or n)?"
if ($confirmation -match "[yY]") {
    pip install psutil
    pip install feedparser
    Write-Host "Script executed."
} else {
    Write-Host "Script exiting."
}