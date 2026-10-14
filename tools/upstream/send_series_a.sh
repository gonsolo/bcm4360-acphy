#!/usr/bin/env bash
# Send series A (cover letter + 2 signed patches, upstream/split/A-list) to linux-wireless with git send-email.
#   tools/upstream/send_series_a.sh --dry-run     show what would be sent (needs no password)
#   tools/upstream/send_series_a.sh               send for real (asks to confirm)
# Recipients: list, wireless maintainers and the blamed/maintainer addresses the netdev CI bot checks (cc_maintainers failed on the first patch without them).
set -eu
P=$(cd "$(dirname "$0")/../.." && pwd); cd "$P"
DRY=; [ "${1:-}" = --dry-run ] && DRY=--dry-run
for p in upstream/split/A-list/000[12]-*.patch; do
	grep -q '^Signed-off-by: Andreas Wendleder <gonsolo@gmail.com>$' "$p" || { echo "$p is not signed off"; exit 1; }
done
if grep -hE '^(To|Cc):' upstream/split/A-list/*.patch | grep -q .; then echo "patches carry recipient headers, stop"; exit 1; fi
git send-email --confirm=always --suppress-cc=all --to-cmd=true --cc-cmd=true $DRY \
	--to 'linux-wireless@vger.kernel.org' \
	--cc 'Johannes Berg <johannes@sipsolutions.net>' \
	--cc 'b43-dev@lists.infradead.org' \
	--cc 'Michael Buesch <m@bues.ch>' \
	--cc 'Alessio Ferri <alessio.ferri@mythread.it>' \
	--cc 'kvalo@kernel.org' \
	--cc 'julian.calaby@gmail.com' \
	--cc 'jpeisach@ubuntu.com' \
	--cc 'linux-kernel@vger.kernel.org' \
	upstream/split/A-list/0*.patch
