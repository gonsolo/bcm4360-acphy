#!/usr/bin/env bash
# Send one of the RFC series B, C or D (cover letter + signed patches, upstream/split/<X>-list) with git send-email.
#   tools/upstream/send_series.sh B --dry-run     show what would be sent
#   tools/upstream/send_series.sh B               send for real (asks to confirm each mail)
# Recipients as for series A (send_series_a.sh), which the netdev CI cc_maintainers check wants. --suppress-cc=all.
set -eu
P=$(cd "$(dirname "$0")/../.." && pwd); cd "$P"
X=${1:?usage: $0 B|C|D [--dry-run]}
case $X in B|C|D) ;; *) echo "series must be B, C or D"; exit 1;; esac
DRY=; [ "${2:-}" = --dry-run ] && DRY=--dry-run
D=upstream/split/$X-list
for p in $D/000[1-9]-*.patch; do
	grep -q '^Signed-off-by: Andreas Wendleder <gonsolo@gmail.com>$' "$p" || { echo "$p is not signed off"; exit 1; }
done
if grep -hE '^(To|Cc):' $D/*.patch | grep -q .; then echo "patches carry recipient headers, stop"; exit 1; fi
git send-email --confirm=${CONFIRM:-always} --suppress-cc=all --to-cmd=true --cc-cmd=true --8bit-encoding=UTF-8 $DRY \
	--to 'linux-wireless@vger.kernel.org' \
	--cc 'Johannes Berg <johannes@sipsolutions.net>' \
	--cc 'b43-dev@lists.infradead.org' \
	--cc 'Alessio Ferri <alessio.ferri@mythread.it>' \
	--cc 'jpeisach@ubuntu.com' \
	--cc 'rosenp@gmail.com' \
	--cc 'linux-kernel@vger.kernel.org' \
	$D/0*.patch
