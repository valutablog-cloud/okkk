    $(document).ready(function() {


        $('#settings').tooltip({ hide: { effect: "fade", duration: 1000 }, position: {
                                       my: "center bottom",
                                       at: "right+50 top"
                                     } });


        function rotateImg(){

            var a = $('#settings').getRotateAngle();

            var d = 90;

            d = +a + +d;

            $("#settings").rotate({animateTo:d});

            $.rot ++;

            if($.rotateimg && $.rot < 5) setTimeout(rotateImg, 200);

        }

        $("#boxip").mouseenter(function() {

            $.rotateimg = true;

            $.rot = 0;

            setTimeout(rotateImg, 200)

          }).mouseleave(function(){$.rotateimg=false;})
          ;


        $.redraw = false;
        $.reset = false;
        $.first = true;

    function AddRow() {

   var myData = [
       { 'intid' : 0, '#': ($("#list").getRowData().length+50), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+51), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+52), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"},
       { 'intid' : 76, '#': "✓" + "&nbsp;" + ($("#list").getRowData().length+100), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;France</span></div>", City: "Katowice", Region: "a"},
           { 'intid' : 0, '#': ($("#list").getRowData().length+53), Country: "<div style=\"display: table;\"><span style=\" width:20px; vertical-align: middle;display: table-cell;\"><img style=\"vertical-align: middle;display: table-cell;margin-right: 1em;\" height=25px src='flag_fr.png' alt='' /></span><span style=\" vertical-align: middle;display: table-cell;\">&nbsp;United States</span></div>", City: "Katowice", Region: "a"}

            ];

           for(var i = 0; i < myData.length; i++) {

                $('#list').jqGrid('addRowData', i, myData[i]);

           }


        }

        setTimeout( AddRow, 1000 );





    function SetSize(){


        $('#list').setGridWidth($("#container").width(), true);
        $('#list').setGridHeight(($("#container").height()-50)+"px", true);
    }



        $(window).resize(function() {

            SetSize();

        });

        $('#list').jqGrid({

            datatype: 'local',

            caption: 'CHOOSE YOUR IP LOCATION',

            height: '350px',

            //width: 400,

            hidegrid: false,

            //altRows: true,

            resizable: false,

            shrinkToFit: true,

            scroll:1,

            pgbuttons:false,

            recordtext: '',

            rowList: [],        // disable page size dropdown

            pgbuttons: false,     // disable page control like next, back button

            pgtext: null,         // disable pager text like 'Page 0 of 10'

            viewrecords: false,   // disable current view record text like 'View 1-10 of 100'

            gridview: true,

            headertitles: true,

            viewrecords: true,

            pager: '',

            onSelectRow: function() {

            return false;
            },

            beforeSelectRow: function() {
            return false;
            },
            resizeStop: function(width, index) {

                $('#gview_list .ui-jqgrid-bdiv div:first-child').css('width',$('#list').css('width'));
                $('#gview_list .ui-jqgrid-bdiv').perfectScrollbar('update');
            },
            onRightClickRow: function () {
            $(this).jqGrid('resetSelection');
            return false;
            },
            onSortCol: function (index, iCol, sortorder) {

            var scrollPosition = $("#list").closest(".ui-jqgrid-bdiv").scrollTop();

            $.redraw = false;

            $.reset = false;

            $.sp = scrollPosition;

            if(scrollPosition <= 1)$.redraw = true;

            else $.reset = true;

            },

            loadComplete: function() {

            SetSize();

                    $('#gview_list div.ui-jqgrid-bdiv').css( {
                    "overflow":"hidden"
                    });

                    $('#gview_list div.ui-jqgrid-bdiv').perfectScrollbar();

                    if($.redraw) this.grid.bDiv.scrollTop = $.sp == 0 ? 1 : 0;

                    //else if($.reset) this.grid.bDiv.scrollTop = $.sp;

                    $.redraw = false;
                    $.reset = false;
            },

            rownumbers: false,

            colNames: ['intid', '#', 'Country', 'City', 'Region'],

            colModel: [

                { name: 'intid', index: 'intid', width: 'auto', sorttype: 'int', hidden: true},

                { name: '#', index: 'id', width: '50', sortable: false, formatter: 'text', align: 'right'},

                { name: 'Country', index: 'Country', width: 150, sorttype: 'text'},

                { name: 'City', index: 'City', width: 120, sorttype: 'text', formatter: 'text' },

                { name: 'Region', index: 'Region', width: 120, sorttype: 'text', formatter: 'text' }

            ]

        });


    });
